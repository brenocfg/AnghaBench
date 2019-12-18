#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int nb_objects; int nb_layers; TYPE_5__* layers; TYPE_1__* objects; } ;
struct TYPE_18__ {int nb_planes; TYPE_2__* planes; } ;
struct TYPE_17__ {int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_16__ {int nb_regions; int /*<<< orphan*/ * length; void** address; } ;
struct TYPE_15__ {size_t object_index; int offset; int /*<<< orphan*/  pitch; } ;
struct TYPE_14__ {int /*<<< orphan*/  size; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ DRMMapping ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVDRMLayerDescriptor ;
typedef  TYPE_6__ AVDRMFrameDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_DRM_MAX_PLANES ; 
 int AV_HWFRAME_MAP_READ ; 
 int AV_HWFRAME_MAP_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_mallocz (int) ; 
 int /*<<< orphan*/  drm_unmap_frame ; 
 int /*<<< orphan*/  errno ; 
 int ff_hwframe_map_create (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__ const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_map_frame(AVHWFramesContext *hwfc,
                         AVFrame *dst, const AVFrame *src, int flags)
{
    const AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)src->data[0];
    DRMMapping *map;
    int err, i, p, plane;
    int mmap_prot;
    void *addr;

    map = av_mallocz(sizeof(*map));
    if (!map)
        return AVERROR(ENOMEM);

    mmap_prot = 0;
    if (flags & AV_HWFRAME_MAP_READ)
        mmap_prot |= PROT_READ;
    if (flags & AV_HWFRAME_MAP_WRITE)
        mmap_prot |= PROT_WRITE;

    av_assert0(desc->nb_objects <= AV_DRM_MAX_PLANES);
    for (i = 0; i < desc->nb_objects; i++) {
        addr = mmap(NULL, desc->objects[i].size, mmap_prot, MAP_SHARED,
                    desc->objects[i].fd, 0);
        if (addr == MAP_FAILED) {
            err = AVERROR(errno);
            av_log(hwfc, AV_LOG_ERROR, "Failed to map DRM object %d to "
                   "memory: %d.\n", desc->objects[i].fd, errno);
            goto fail;
        }

        map->address[i] = addr;
        map->length[i]  = desc->objects[i].size;
    }
    map->nb_regions = i;

    plane = 0;
    for (i = 0; i < desc->nb_layers; i++) {
        const AVDRMLayerDescriptor *layer = &desc->layers[i];
        for (p = 0; p < layer->nb_planes; p++) {
            dst->data[plane] =
                (uint8_t*)map->address[layer->planes[p].object_index] +
                                       layer->planes[p].offset;
            dst->linesize[plane] =     layer->planes[p].pitch;
            ++plane;
        }
    }
    av_assert0(plane <= AV_DRM_MAX_PLANES);

    dst->width  = src->width;
    dst->height = src->height;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &drm_unmap_frame, map);
    if (err < 0)
        goto fail;

    return 0;

fail:
    for (i = 0; i < desc->nb_objects; i++) {
        if (map->address[i])
            munmap(map->address[i], map->length[i]);
    }
    av_free(map);
    return err;
}