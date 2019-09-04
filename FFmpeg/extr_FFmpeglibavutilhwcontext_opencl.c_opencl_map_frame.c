#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/  cl_map_flags ;
typedef  int /*<<< orphan*/  cl_int ;
typedef  int /*<<< orphan*/  cl_image_format ;
struct TYPE_19__ {size_t image_width; size_t image_height; } ;
typedef  TYPE_2__ cl_image_desc ;
typedef  int /*<<< orphan*/  cl_event ;
struct TYPE_23__ {scalar_t__ format; scalar_t__* data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_22__ {scalar_t__ sw_format; TYPE_1__* internal; } ;
struct TYPE_21__ {int /*<<< orphan*/  command_queue; } ;
struct TYPE_20__ {scalar_t__* address; } ;
struct TYPE_18__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ OpenCLMapping ;
typedef  TYPE_4__ OpenCLFramesContext ;
typedef  TYPE_5__ AVHWFramesContext ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_HWFRAME_MAP_OVERWRITE ; 
 int AV_HWFRAME_MAP_READ ; 
 int AV_HWFRAME_MAP_WRITE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  CL_FALSE ; 
 int /*<<< orphan*/  CL_MAP_READ ; 
 int /*<<< orphan*/  CL_MAP_WRITE ; 
 int /*<<< orphan*/  CL_MAP_WRITE_INVALIDATE_REGION ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 TYPE_3__* av_mallocz (int) ; 
 scalar_t__ clEnqueueMapImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clEnqueueUnmapMemObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_hwframe_map_create (int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__ const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int opencl_get_plane_format (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  opencl_unmap_frame ; 
 int opencl_wait_events (TYPE_5__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            const AVFrame *src, int flags)
{
    OpenCLFramesContext *priv = hwfc->internal->priv;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t row_pitch;
    cl_event events[AV_NUM_DATA_POINTERS];
    int err, p;

    av_assert0(hwfc->sw_format == dst->format);

    if (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } else {
        map_flags = 0;
        if (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        if (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(sizeof(*map));
    if (!map)
        return AVERROR(ENOMEM);

    for (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        if (err == AVERROR(ENOENT))
            break;
        if (err < 0)
            goto fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, NULL, 0, NULL,
                              &events[p], &cle);
        if (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            goto fail;
        }

        dst->data[p] = map->address[p];

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    if (err < 0)
        goto fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    if (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    return 0;

fail:
    for (p = 0; p < AV_NUM_DATA_POINTERS; p++) {
        if (!map->address[p])
            break;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, NULL, &events[p]);
    }
    if (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    return err;
}