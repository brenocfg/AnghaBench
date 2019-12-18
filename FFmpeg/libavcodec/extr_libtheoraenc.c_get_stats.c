#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int stats_offset; void* stats; int /*<<< orphan*/  stats_size; int /*<<< orphan*/  t_state; } ;
typedef  TYPE_1__ TheoraContext ;
struct TYPE_6__ {int /*<<< orphan*/  stats_out; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int AV_BASE64_SIZE (int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSUP ; 
 int /*<<< orphan*/  TH_ENCCTL_2PASS_OUT ; 
 int /*<<< orphan*/  av_base64_encode (int /*<<< orphan*/ ,int,void*,int) ; 
 void* av_fast_realloc (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int th_encode_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

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