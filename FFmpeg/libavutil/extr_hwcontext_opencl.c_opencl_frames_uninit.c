#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_int ;
struct TYPE_11__ {TYPE_1__* internal; } ;
struct TYPE_10__ {int nb_planes; int /*<<< orphan*/ * planes; } ;
struct TYPE_9__ {int nb_mapped_frames; int /*<<< orphan*/ * command_queue; TYPE_3__* mapped_frames; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ OpenCLFramesContext ;
typedef  TYPE_3__ AVOpenCLFrameDescriptor ;
typedef  TYPE_4__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CL_SUCCESS ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  clReleaseCommandQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clReleaseMemObject (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->internal->priv;
    cl_int cle;

#if HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    int i, p;
    for (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        for (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            if (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    if (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        if (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = NULL;
    }
}