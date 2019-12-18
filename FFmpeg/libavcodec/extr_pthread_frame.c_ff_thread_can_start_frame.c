#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int active_thread_type; TYPE_2__* codec; TYPE_1__* internal; } ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {scalar_t__ update_thread_context; } ;
struct TYPE_7__ {TYPE_3__* thread_ctx; } ;
typedef  TYPE_3__ PerThreadContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int FF_THREAD_FRAME ; 
 scalar_t__ STATE_SETTING_UP ; 
 int /*<<< orphan*/  THREAD_SAFE_CALLBACKS (TYPE_4__*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 

int ff_thread_can_start_frame(AVCodecContext *avctx)
{
    PerThreadContext *p = avctx->internal->thread_ctx;
    if ((avctx->active_thread_type&FF_THREAD_FRAME) && atomic_load(&p->state) != STATE_SETTING_UP &&
        (avctx->codec->update_thread_context || !THREAD_SAFE_CALLBACKS(avctx))) {
        return 0;
    }
    return 1;
}