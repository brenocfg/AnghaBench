#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ sz; int /*<<< orphan*/ * buf; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
struct TYPE_6__ {TYPE_1__ frame; } ;
struct vpx_codec_cx_pkt {TYPE_2__ data; } ;
struct FrameListData {int flags; int frame_number; scalar_t__ sz_alpha; int /*<<< orphan*/ * buf_alpha; int /*<<< orphan*/  sse; scalar_t__ have_sse; int /*<<< orphan*/ * buf; scalar_t__ sz; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
struct TYPE_7__ {int frame_number; scalar_t__ have_sse; int /*<<< orphan*/  sse; } ;
typedef  TYPE_3__ VPxContext ;

/* Variables and functions */
 int VPX_FRAME_IS_INVISIBLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cx_pktcpy(struct FrameListData *dst,
                             const struct vpx_codec_cx_pkt *src,
                             const struct vpx_codec_cx_pkt *src_alpha,
                             VPxContext *ctx)
{
    dst->pts      = src->data.frame.pts;
    dst->duration = src->data.frame.duration;
    dst->flags    = src->data.frame.flags;
    dst->sz       = src->data.frame.sz;
    dst->buf      = src->data.frame.buf;
    dst->have_sse = 0;
    /* For alt-ref frame, don't store PSNR or increment frame_number */
    if (!(dst->flags & VPX_FRAME_IS_INVISIBLE)) {
        dst->frame_number = ++ctx->frame_number;
        dst->have_sse = ctx->have_sse;
        if (ctx->have_sse) {
            /* associate last-seen SSE to the frame. */
            /* Transfers ownership from ctx to dst. */
            /* WARNING! This makes the assumption that PSNR_PKT comes
               just before the frame it refers to! */
            memcpy(dst->sse, ctx->sse, sizeof(dst->sse));
            ctx->have_sse = 0;
        }
    } else {
        dst->frame_number = -1;   /* sanity marker */
    }
    if (src_alpha) {
        dst->buf_alpha = src_alpha->data.frame.buf;
        dst->sz_alpha = src_alpha->data.frame.sz;
    } else {
        dst->buf_alpha = NULL;
        dst->sz_alpha = 0;
    }
}