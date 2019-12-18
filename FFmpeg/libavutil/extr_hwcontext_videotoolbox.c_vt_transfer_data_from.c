#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  format; } ;
struct TYPE_13__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_HWFRAME_MAP_READ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_frame_alloc () ; 
 int av_frame_copy (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int vt_map_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    int err;

    if (dst->width > hwfc->width || dst->height > hwfc->height)
        return AVERROR(EINVAL);

    map = av_frame_alloc();
    if (!map)
        return AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    if (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    if (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    return err;
}