#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nb_channels; int*** coding_method; float*** sb_samples; float*** tone_level; int /*<<< orphan*/  noise_idx; } ;
typedef  TYPE_1__ QDM2Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int FF_ARRAY_ELEMS (float*) ; 
 int /*<<< orphan*/  FIX_NOISE_IDX (int /*<<< orphan*/ ) ; 
 float SB_DITHERING_NOISE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  build_sb_samples_from_noise (TYPE_1__*,int) ; 
 float** dequant_1bit ; 
 scalar_t__ fix_coding_method_array (int,int,int***) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 double* noise_samples ; 
 unsigned int qdm2_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t** random_dequant_index ; 
 int /*<<< orphan*/ ** random_dequant_type24 ; 
 float* type30_dequant ; 
 float* type34_delta ; 
 int /*<<< orphan*/  vlc_tab_type30 ; 
 int /*<<< orphan*/  vlc_tab_type34 ; 

__attribute__((used)) static int synthfilt_build_sb_samples(QDM2Context *q, GetBitContext *gb,
                                       int length, int sb_min, int sb_max)
{
    int sb, j, k, n, ch, run, channels;
    int joined_stereo, zero_encoding;
    int type34_first;
    float type34_div = 0;
    float type34_predictor;
    float samples[10];
    int sign_bits[16] = {0};

    if (length == 0) {
        // If no data use noise
        for (sb=sb_min; sb < sb_max; sb++)
            build_sb_samples_from_noise(q, sb);

        return 0;
    }

    for (sb = sb_min; sb < sb_max; sb++) {
        channels = q->nb_channels;

        if (q->nb_channels <= 1 || sb < 12)
            joined_stereo = 0;
        else if (sb >= 24)
            joined_stereo = 1;
        else
            joined_stereo = (get_bits_left(gb) >= 1) ? get_bits1(gb) : 0;

        if (joined_stereo) {
            if (get_bits_left(gb) >= 16)
                for (j = 0; j < 16; j++)
                    sign_bits[j] = get_bits1(gb);

            for (j = 0; j < 64; j++)
                if (q->coding_method[1][sb][j] > q->coding_method[0][sb][j])
                    q->coding_method[0][sb][j] = q->coding_method[1][sb][j];

            if (fix_coding_method_array(sb, q->nb_channels,
                                            q->coding_method)) {
                av_log(NULL, AV_LOG_ERROR, "coding method invalid\n");
                build_sb_samples_from_noise(q, sb);
                continue;
            }
            channels = 1;
        }

        for (ch = 0; ch < channels; ch++) {
            FIX_NOISE_IDX(q->noise_idx);
            zero_encoding = (get_bits_left(gb) >= 1) ? get_bits1(gb) : 0;
            type34_predictor = 0.0;
            type34_first = 1;

            for (j = 0; j < 128; ) {
                switch (q->coding_method[ch][sb][j / 2]) {
                    case 8:
                        if (get_bits_left(gb) >= 10) {
                            if (zero_encoding) {
                                for (k = 0; k < 5; k++) {
                                    if ((j + 2 * k) >= 128)
                                        break;
                                    samples[2 * k] = get_bits1(gb) ? dequant_1bit[joined_stereo][2 * get_bits1(gb)] : 0;
                                }
                            } else {
                                n = get_bits(gb, 8);
                                if (n >= 243) {
                                    av_log(NULL, AV_LOG_ERROR, "Invalid 8bit codeword\n");
                                    return AVERROR_INVALIDDATA;
                                }

                                for (k = 0; k < 5; k++)
                                    samples[2 * k] = dequant_1bit[joined_stereo][random_dequant_index[n][k]];
                            }
                            for (k = 0; k < 5; k++)
                                samples[2 * k + 1] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        } else {
                            for (k = 0; k < 10; k++)
                                samples[k] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        }
                        run = 10;
                        break;

                    case 10:
                        if (get_bits_left(gb) >= 1) {
                            float f = 0.81;

                            if (get_bits1(gb))
                                f = -f;
                            f -= noise_samples[((sb + 1) * (j +5 * ch + 1)) & 127] * 9.0 / 40.0;
                            samples[0] = f;
                        } else {
                            samples[0] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        }
                        run = 1;
                        break;

                    case 16:
                        if (get_bits_left(gb) >= 10) {
                            if (zero_encoding) {
                                for (k = 0; k < 5; k++) {
                                    if ((j + k) >= 128)
                                        break;
                                    samples[k] = (get_bits1(gb) == 0) ? 0 : dequant_1bit[joined_stereo][2 * get_bits1(gb)];
                                }
                            } else {
                                n = get_bits (gb, 8);
                                if (n >= 243) {
                                    av_log(NULL, AV_LOG_ERROR, "Invalid 8bit codeword\n");
                                    return AVERROR_INVALIDDATA;
                                }

                                for (k = 0; k < 5; k++)
                                    samples[k] = dequant_1bit[joined_stereo][random_dequant_index[n][k]];
                            }
                        } else {
                            for (k = 0; k < 5; k++)
                                samples[k] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        }
                        run = 5;
                        break;

                    case 24:
                        if (get_bits_left(gb) >= 7) {
                            n = get_bits(gb, 7);
                            if (n >= 125) {
                                av_log(NULL, AV_LOG_ERROR, "Invalid 7bit codeword\n");
                                return AVERROR_INVALIDDATA;
                            }

                            for (k = 0; k < 3; k++)
                                samples[k] = (random_dequant_type24[n][k] - 2.0) * 0.5;
                        } else {
                            for (k = 0; k < 3; k++)
                                samples[k] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        }
                        run = 3;
                        break;

                    case 30:
                        if (get_bits_left(gb) >= 4) {
                            unsigned index = qdm2_get_vlc(gb, &vlc_tab_type30, 0, 1);
                            if (index >= FF_ARRAY_ELEMS(type30_dequant)) {
                                av_log(NULL, AV_LOG_ERROR, "index %d out of type30_dequant array\n", index);
                                return AVERROR_INVALIDDATA;
                            }
                            samples[0] = type30_dequant[index];
                        } else
                            samples[0] = SB_DITHERING_NOISE(sb,q->noise_idx);

                        run = 1;
                        break;

                    case 34:
                        if (get_bits_left(gb) >= 7) {
                            if (type34_first) {
                                type34_div = (float)(1 << get_bits(gb, 2));
                                samples[0] = ((float)get_bits(gb, 5) - 16.0) / 15.0;
                                type34_predictor = samples[0];
                                type34_first = 0;
                            } else {
                                unsigned index = qdm2_get_vlc(gb, &vlc_tab_type34, 0, 1);
                                if (index >= FF_ARRAY_ELEMS(type34_delta)) {
                                    av_log(NULL, AV_LOG_ERROR, "index %d out of type34_delta array\n", index);
                                    return AVERROR_INVALIDDATA;
                                }
                                samples[0] = type34_delta[index] / type34_div + type34_predictor;
                                type34_predictor = samples[0];
                            }
                        } else {
                            samples[0] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        }
                        run = 1;
                        break;

                    default:
                        samples[0] = SB_DITHERING_NOISE(sb,q->noise_idx);
                        run = 1;
                        break;
                }

                if (joined_stereo) {
                    for (k = 0; k < run && j + k < 128; k++) {
                        q->sb_samples[0][j + k][sb] =
                            q->tone_level[0][sb][(j + k) / 2] * samples[k];
                        if (q->nb_channels == 2) {
                            if (sign_bits[(j + k) / 8])
                                q->sb_samples[1][j + k][sb] =
                                    q->tone_level[1][sb][(j + k) / 2] * -samples[k];
                            else
                                q->sb_samples[1][j + k][sb] =
                                    q->tone_level[1][sb][(j + k) / 2] * samples[k];
                        }
                    }
                } else {
                    for (k = 0; k < run; k++)
                        if ((j + k) < 128)
                            q->sb_samples[ch][j + k][sb] = q->tone_level[ch][sb][(j + k)/2] * samples[k];
                }

                j += run;
            } // j loop
        } // channel loop
    } // subband loop
    return 0;
}