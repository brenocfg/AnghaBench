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
typedef  scalar_t__ cl_int ;
struct TYPE_6__ {TYPE_1__* hwctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ AVOpenCLDeviceContext ;
typedef  TYPE_2__ AVHWDeviceContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ clReleaseContext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    if (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}