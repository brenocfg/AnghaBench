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
struct TYPE_5__ {int /*<<< orphan*/  current_frame; int /*<<< orphan*/  golden_frame; scalar_t__ keyframe; int /*<<< orphan*/  last_frame; } ;
typedef  TYPE_1__ Vp3DecodeContext ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int ff_thread_ref_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_frames(AVCodecContext *avctx)
{
    Vp3DecodeContext *s = avctx->priv_data;
    int ret = 0;

    /* shuffle frames (last = current) */
    ff_thread_release_buffer(avctx, &s->last_frame);
    ret = ff_thread_ref_frame(&s->last_frame, &s->current_frame);
    if (ret < 0)
        goto fail;

    if (s->keyframe) {
        ff_thread_release_buffer(avctx, &s->golden_frame);
        ret = ff_thread_ref_frame(&s->golden_frame, &s->current_frame);
    }

fail:
    ff_thread_release_buffer(avctx, &s->current_frame);
    return ret;
}