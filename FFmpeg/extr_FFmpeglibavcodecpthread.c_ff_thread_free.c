#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int active_thread_type; int /*<<< orphan*/  thread_count; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/  ff_frame_thread_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_slice_thread_free (TYPE_1__*) ; 

void ff_thread_free(AVCodecContext *avctx)
{
    if (avctx->active_thread_type&FF_THREAD_FRAME)
        ff_frame_thread_free(avctx, avctx->thread_count);
    else
        ff_slice_thread_free(avctx);
}