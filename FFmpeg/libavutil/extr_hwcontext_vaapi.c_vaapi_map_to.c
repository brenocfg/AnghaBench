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
struct TYPE_6__ {int format; } ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_DRM_PRIME 128 
 int /*<<< orphan*/  ENOSYS ; 
 int vaapi_map_from_drm (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static int vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        const AVFrame *src, int flags)
{
    switch (src->format) {
#if CONFIG_LIBDRM
    case AV_PIX_FMT_DRM_PRIME:
        return vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    default:
        return AVERROR(ENOSYS);
    }
}