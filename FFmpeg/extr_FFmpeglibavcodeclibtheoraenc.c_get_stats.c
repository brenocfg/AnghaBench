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
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOSUP ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_stats(AVCodecContext *avctx, int eos)
{
#ifdef TH_ENCCTL_2PASS_OUT
    TheoraContext *h = avctx->priv_data;
    uint8_t *buf;
    int bytes;

    bytes = th_encode_ctl(h->t_state, TH_ENCCTL_2PASS_OUT, &buf, sizeof(buf));
    if (bytes < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error getting first pass stats\n");
        return AVERROR_EXTERNAL;
    }
    if (!eos) {
        void *tmp = av_fast_realloc(h->stats, &h->stats_size,
                                   h->stats_offset + bytes);
        if (!tmp)
            return AVERROR(ENOMEM);
        h->stats = tmp;
        memcpy(h->stats + h->stats_offset, buf, bytes);
        h->stats_offset += bytes;
    } else {
        int b64_size = AV_BASE64_SIZE(h->stats_offset);
        // libtheora generates a summary header at the end
        memcpy(h->stats, buf, bytes);
        avctx->stats_out = av_malloc(b64_size);
        if (!avctx->stats_out)
            return AVERROR(ENOMEM);
        av_base64_encode(avctx->stats_out, b64_size, h->stats, h->stats_offset);
    }
    return 0;
#else
    av_log(avctx, AV_LOG_ERROR, "libtheora too old to support 2pass\n");
    return AVERROR(ENOSUP);
#endif
}