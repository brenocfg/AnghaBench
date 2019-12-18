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
typedef  int /*<<< orphan*/  vpx_codec_ctx_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ VPX_CODEC_OK ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ vpx_codec_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vpx_codec_error (int /*<<< orphan*/ *) ; 
 char* vpx_codec_error_detail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, vpx_codec_ctx_t *decoder,
                        uint8_t *data, uint32_t data_sz)
{
    if (vpx_codec_decode(decoder, data, data_sz, NULL, 0) != VPX_CODEC_OK) {
        const char *error  = vpx_codec_error(decoder);
        const char *detail = vpx_codec_error_detail(decoder);

        av_log(avctx, AV_LOG_ERROR, "Failed to decode frame: %s\n", error);
        if (detail) {
            av_log(avctx, AV_LOG_ERROR, "  Additional information: %s\n",
                   detail);
        }
        return AVERROR_INVALIDDATA;
    }
    return 0;
}