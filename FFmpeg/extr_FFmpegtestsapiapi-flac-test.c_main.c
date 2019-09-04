#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AV_CH_LAYOUT_5POINT1_BACK ; 
 int AV_CH_LAYOUT_STEREO ; 
 int AV_CH_LAYOUT_STEREO_DOWNMIX ; 
 int AV_CH_LAYOUT_SURROUND ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLAC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_decoder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  close_encoder (int /*<<< orphan*/ **) ; 
 scalar_t__ init_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 scalar_t__ init_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 
 scalar_t__ run_test (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(void)
{
    AVCodec *enc = NULL, *dec = NULL;
    AVCodecContext *enc_ctx = NULL, *dec_ctx = NULL;
    uint64_t channel_layouts[] = {AV_CH_LAYOUT_STEREO, AV_CH_LAYOUT_5POINT1_BACK, AV_CH_LAYOUT_SURROUND, AV_CH_LAYOUT_STEREO_DOWNMIX};
    int sample_rates[] = {8000, 44100, 48000, 192000};
    int cl, sr;

    enc = avcodec_find_encoder(AV_CODEC_ID_FLAC);
    if (!enc) {
        av_log(NULL, AV_LOG_ERROR, "Can't find encoder\n");
        return 1;
    }

    dec = avcodec_find_decoder(AV_CODEC_ID_FLAC);
    if (!dec) {
        av_log(NULL, AV_LOG_ERROR, "Can't find decoder\n");
        return 1;
    }

    for (cl = 0; cl < FF_ARRAY_ELEMS(channel_layouts); cl++) {
        for (sr = 0; sr < FF_ARRAY_ELEMS(sample_rates); sr++) {
            if (init_encoder(enc, &enc_ctx, channel_layouts[cl], sample_rates[sr]) != 0)
                return 1;
            if (init_decoder(dec, &dec_ctx, channel_layouts[cl]) != 0)
                return 1;
            if (run_test(enc, dec, enc_ctx, dec_ctx) != 0)
                return 1;
            close_encoder(&enc_ctx);
            close_decoder(&dec_ctx);
        }
    }

    return 0;
}