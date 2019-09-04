#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VLC_TYPE ;
struct TYPE_11__ {int /*<<< orphan*/ ** table; } ;
struct TYPE_10__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {int bs_num_env; size_t* bs_freq_res; int** env_facs_q; scalar_t__* bs_df_env; scalar_t__ bs_amp_res; } ;
struct TYPE_8__ {int bs_coupling; int* n; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t F_HUFFMAN_ENV_1_5DB ; 
 size_t F_HUFFMAN_ENV_3_0DB ; 
 size_t F_HUFFMAN_ENV_BAL_1_5DB ; 
 size_t F_HUFFMAN_ENV_BAL_3_0DB ; 
 size_t T_HUFFMAN_ENV_1_5DB ; 
 size_t T_HUFFMAN_ENV_3_0DB ; 
 size_t T_HUFFMAN_ENV_BAL_1_5DB ; 
 size_t T_HUFFMAN_ENV_BAL_3_0DB ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int const get_bits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 TYPE_4__* vlc_sbr ; 
 int* vlc_sbr_lav ; 

__attribute__((used)) static int read_sbr_envelope(AACContext *ac, SpectralBandReplication *sbr, GetBitContext *gb,
                              SBRData *ch_data, int ch)
{
    int bits;
    int i, j, k;
    VLC_TYPE (*t_huff)[2], (*f_huff)[2];
    int t_lav, f_lav;
    const int delta = (ch == 1 && sbr->bs_coupling == 1) + 1;
    const int odd = sbr->n[1] & 1;

    if (sbr->bs_coupling && ch) {
        if (ch_data->bs_amp_res) {
            bits   = 5;
            t_huff = vlc_sbr[T_HUFFMAN_ENV_BAL_3_0DB].table;
            t_lav  = vlc_sbr_lav[T_HUFFMAN_ENV_BAL_3_0DB];
            f_huff = vlc_sbr[F_HUFFMAN_ENV_BAL_3_0DB].table;
            f_lav  = vlc_sbr_lav[F_HUFFMAN_ENV_BAL_3_0DB];
        } else {
            bits   = 6;
            t_huff = vlc_sbr[T_HUFFMAN_ENV_BAL_1_5DB].table;
            t_lav  = vlc_sbr_lav[T_HUFFMAN_ENV_BAL_1_5DB];
            f_huff = vlc_sbr[F_HUFFMAN_ENV_BAL_1_5DB].table;
            f_lav  = vlc_sbr_lav[F_HUFFMAN_ENV_BAL_1_5DB];
        }
    } else {
        if (ch_data->bs_amp_res) {
            bits   = 6;
            t_huff = vlc_sbr[T_HUFFMAN_ENV_3_0DB].table;
            t_lav  = vlc_sbr_lav[T_HUFFMAN_ENV_3_0DB];
            f_huff = vlc_sbr[F_HUFFMAN_ENV_3_0DB].table;
            f_lav  = vlc_sbr_lav[F_HUFFMAN_ENV_3_0DB];
        } else {
            bits   = 7;
            t_huff = vlc_sbr[T_HUFFMAN_ENV_1_5DB].table;
            t_lav  = vlc_sbr_lav[T_HUFFMAN_ENV_1_5DB];
            f_huff = vlc_sbr[F_HUFFMAN_ENV_1_5DB].table;
            f_lav  = vlc_sbr_lav[F_HUFFMAN_ENV_1_5DB];
        }
    }

    for (i = 0; i < ch_data->bs_num_env; i++) {
        if (ch_data->bs_df_env[i]) {
            // bs_freq_res[0] == bs_freq_res[bs_num_env] from prev frame
            if (ch_data->bs_freq_res[i + 1] == ch_data->bs_freq_res[i]) {
                for (j = 0; j < sbr->n[ch_data->bs_freq_res[i + 1]]; j++) {
                    ch_data->env_facs_q[i + 1][j] = ch_data->env_facs_q[i][j] + delta * (get_vlc2(gb, t_huff, 9, 3) - t_lav);
                    if (ch_data->env_facs_q[i + 1][j] > 127U) {
                        av_log(ac->avctx, AV_LOG_ERROR, "env_facs_q %d is invalid\n", ch_data->env_facs_q[i + 1][j]);
                        return AVERROR_INVALIDDATA;
                    }
                }
            } else if (ch_data->bs_freq_res[i + 1]) {
                for (j = 0; j < sbr->n[ch_data->bs_freq_res[i + 1]]; j++) {
                    k = (j + odd) >> 1; // find k such that f_tablelow[k] <= f_tablehigh[j] < f_tablelow[k + 1]
                    ch_data->env_facs_q[i + 1][j] = ch_data->env_facs_q[i][k] + delta * (get_vlc2(gb, t_huff, 9, 3) - t_lav);
                    if (ch_data->env_facs_q[i + 1][j] > 127U) {
                        av_log(ac->avctx, AV_LOG_ERROR, "env_facs_q %d is invalid\n", ch_data->env_facs_q[i + 1][j]);
                        return AVERROR_INVALIDDATA;
                    }
                }
            } else {
                for (j = 0; j < sbr->n[ch_data->bs_freq_res[i + 1]]; j++) {
                    k = j ? 2*j - odd : 0; // find k such that f_tablehigh[k] == f_tablelow[j]
                    ch_data->env_facs_q[i + 1][j] = ch_data->env_facs_q[i][k] + delta * (get_vlc2(gb, t_huff, 9, 3) - t_lav);
                    if (ch_data->env_facs_q[i + 1][j] > 127U) {
                        av_log(ac->avctx, AV_LOG_ERROR, "env_facs_q %d is invalid\n", ch_data->env_facs_q[i + 1][j]);
                        return AVERROR_INVALIDDATA;
                    }
                }
            }
        } else {
            ch_data->env_facs_q[i + 1][0] = delta * get_bits(gb, bits); // bs_env_start_value_balance
            for (j = 1; j < sbr->n[ch_data->bs_freq_res[i + 1]]; j++) {
                ch_data->env_facs_q[i + 1][j] = ch_data->env_facs_q[i + 1][j - 1] + delta * (get_vlc2(gb, f_huff, 9, 3) - f_lav);
                if (ch_data->env_facs_q[i + 1][j] > 127U) {
                    av_log(ac->avctx, AV_LOG_ERROR, "env_facs_q %d is invalid\n", ch_data->env_facs_q[i + 1][j]);
                    return AVERROR_INVALIDDATA;
                }
            }
        }
    }

    //assign 0th elements of env_facs_q from last elements
    memcpy(ch_data->env_facs_q[0], ch_data->env_facs_q[ch_data->bs_num_env],
           sizeof(ch_data->env_facs_q[0]));

    return 0;
}