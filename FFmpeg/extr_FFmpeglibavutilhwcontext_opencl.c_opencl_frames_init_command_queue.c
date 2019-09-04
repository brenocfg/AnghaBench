#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cl_int ;
struct TYPE_16__ {TYPE_3__* internal; TYPE_2__* device_ctx; TYPE_6__* hwctx; } ;
struct TYPE_15__ {scalar_t__ command_queue; } ;
struct TYPE_14__ {scalar_t__ command_queue; } ;
struct TYPE_13__ {scalar_t__ command_queue; } ;
struct TYPE_12__ {TYPE_4__* priv; } ;
struct TYPE_11__ {TYPE_1__* internal; } ;
struct TYPE_10__ {TYPE_5__* priv; } ;
typedef  TYPE_4__ OpenCLFramesContext ;
typedef  TYPE_5__ OpenCLDeviceContext ;
typedef  TYPE_6__ AVOpenCLFramesContext ;
typedef  TYPE_7__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ clRetainCommandQueue (scalar_t__) ; 

__attribute__((used)) static int opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    AVOpenCLFramesContext *hwctx = hwfc->hwctx;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->internal->priv;
    OpenCLFramesContext    *priv = hwfc->internal->priv;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    if (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        return AVERROR(EIO);
    }

    return 0;
}