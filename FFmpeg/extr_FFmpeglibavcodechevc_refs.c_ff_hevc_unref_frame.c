#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/ * hwaccel_picture_private; int /*<<< orphan*/  hwaccel_priv_buf; int /*<<< orphan*/ * collocated_ref; int /*<<< orphan*/ * refPicList; int /*<<< orphan*/ * rpl_tab; int /*<<< orphan*/  rpl_tab_buf; int /*<<< orphan*/  rpl_buf; int /*<<< orphan*/ * tab_mvf; int /*<<< orphan*/  tab_mvf_buf; int /*<<< orphan*/  tf; TYPE_1__* frame; } ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ HEVCFrame ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ff_hevc_unref_frame(HEVCContext *s, HEVCFrame *frame, int flags)
{
    /* frame->frame can be NULL if context init failed */
    if (!frame->frame || !frame->frame->buf[0])
        return;

    frame->flags &= ~flags;
    if (!frame->flags) {
        ff_thread_release_buffer(s->avctx, &frame->tf);

        av_buffer_unref(&frame->tab_mvf_buf);
        frame->tab_mvf = NULL;

        av_buffer_unref(&frame->rpl_buf);
        av_buffer_unref(&frame->rpl_tab_buf);
        frame->rpl_tab    = NULL;
        frame->refPicList = NULL;

        frame->collocated_ref = NULL;

        av_buffer_unref(&frame->hwaccel_priv_buf);
        frame->hwaccel_picture_private = NULL;
    }
}