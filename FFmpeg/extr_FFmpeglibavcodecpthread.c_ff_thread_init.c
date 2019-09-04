#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int active_thread_type; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int FF_THREAD_FRAME ; 
 int FF_THREAD_SLICE ; 
 int ff_frame_thread_init (TYPE_1__*) ; 
 int ff_slice_thread_init (TYPE_1__*) ; 
 int /*<<< orphan*/  validate_thread_parameters (TYPE_1__*) ; 

int ff_thread_init(AVCodecContext *avctx)
{
    validate_thread_parameters(avctx);

    if (avctx->active_thread_type&FF_THREAD_SLICE)
        return ff_slice_thread_init(avctx);
    else if (avctx->active_thread_type&FF_THREAD_FRAME)
        return ff_frame_thread_init(avctx);

    return 0;
}