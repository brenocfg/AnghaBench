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
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int mmap_read_frame (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int v4l2_read_packet(AVFormatContext *ctx, AVPacket *pkt)
{
#if FF_API_CODED_FRAME && FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
    struct video_data *s = ctx->priv_data;
    AVFrame *frame = ctx->streams[0]->codec->coded_frame;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    int res;

    if ((res = mmap_read_frame(ctx, pkt)) < 0) {
        return res;
    }

#if FF_API_CODED_FRAME && FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
    if (frame && s->interlaced) {
        frame->interlaced_frame = 1;
        frame->top_field_first = s->top_field_first;
    }
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    return pkt->size;
}