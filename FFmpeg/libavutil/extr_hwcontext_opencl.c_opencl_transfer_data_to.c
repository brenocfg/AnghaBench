#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_mem ;
typedef  scalar_t__ cl_int ;
typedef  int /*<<< orphan*/  cl_image_format ;
struct TYPE_13__ {size_t image_width; size_t image_height; } ;
typedef  TYPE_2__ cl_image_desc ;
typedef  int /*<<< orphan*/  cl_event ;
struct TYPE_16__ {scalar_t__ format; scalar_t__* data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {scalar_t__ sw_format; TYPE_1__* internal; } ;
struct TYPE_14__ {int /*<<< orphan*/  command_queue; } ;
struct TYPE_12__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ OpenCLFramesContext ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  CL_FALSE ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ clEnqueueWriteImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int opencl_get_plane_format (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  opencl_wait_events (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, const AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->internal->priv;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_NUM_DATA_POINTERS];
    int err, p;

    if (src->format != hwfc->sw_format)
        return AVERROR(EINVAL);

    for (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        if (err < 0) {
            if (err == AVERROR(ENOENT))
                err = 0;
            break;
        }

        if (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            break;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, NULL, &events[p]);
        if (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            break;
        }
    }

    opencl_wait_events(hwfc, events, p);

    return err;
}