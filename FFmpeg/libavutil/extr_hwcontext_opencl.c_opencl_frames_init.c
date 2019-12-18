#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_mem ;
struct TYPE_7__ {TYPE_1__* internal; int /*<<< orphan*/  pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  pool_internal; } ;
typedef  TYPE_2__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_pool_init2 (int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int opencl_frames_init_command_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  opencl_pool_alloc ; 

__attribute__((used)) static int opencl_frames_init(AVHWFramesContext *hwfc)
{
    if (!hwfc->pool) {
        hwfc->internal->pool_internal =
            av_buffer_pool_init2(sizeof(cl_mem), hwfc,
                                 &opencl_pool_alloc, NULL);
        if (!hwfc->internal->pool_internal)
            return AVERROR(ENOMEM);
    }

    return opencl_frames_init_command_queue(hwfc);
}