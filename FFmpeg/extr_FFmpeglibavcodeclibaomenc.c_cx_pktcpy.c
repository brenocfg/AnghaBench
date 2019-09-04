#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  sz; int /*<<< orphan*/  flags; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
struct TYPE_4__ {TYPE_1__ frame; } ;
struct aom_codec_cx_pkt {TYPE_2__ data; } ;
struct FrameListData {int /*<<< orphan*/  buf; int /*<<< orphan*/  sz; int /*<<< orphan*/  flags; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
typedef  int /*<<< orphan*/  AOMContext ;

/* Variables and functions */

__attribute__((used)) static inline void cx_pktcpy(AOMContext *ctx,
                             struct FrameListData *dst,
                             const struct aom_codec_cx_pkt *src)
{
    dst->pts      = src->data.frame.pts;
    dst->duration = src->data.frame.duration;
    dst->flags    = src->data.frame.flags;
    dst->sz       = src->data.frame.sz;
    dst->buf      = src->data.frame.buf;
#ifdef AOM_FRAME_IS_INTRAONLY
    dst->have_sse = 0;
    dst->frame_number = ++ctx->frame_number;
    dst->have_sse = ctx->have_sse;
    if (ctx->have_sse) {
        /* associate last-seen SSE to the frame. */
        /* Transfers ownership from ctx to dst. */
        memcpy(dst->sse, ctx->sse, sizeof(dst->sse));
        ctx->have_sse = 0;
    }
#endif
}