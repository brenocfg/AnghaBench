#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ format; } ;
struct TYPE_11__ {scalar_t__ sw_format; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int av_frame_copy_props (TYPE_2__*,TYPE_2__ const*) ; 
 int drm_map_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int drm_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                        const AVFrame *src, int flags)
{
    int err;

    if (hwfc->sw_format != dst->format)
        return AVERROR(ENOSYS);

    err = drm_map_frame(hwfc, dst, src, flags);
    if (err)
        return err;

    err = av_frame_copy_props(dst, src);
    if (err)
        return err;

    return 0;
}