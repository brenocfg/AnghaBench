#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int format; } ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
#define  AV_PIX_FMT_DRM_PRIME 128 
 int vaapi_map_to_drm (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__ const*,int) ; 
 int vaapi_map_to_memory (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static int vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          const AVFrame *src, int flags)
{
    switch (dst->format) {
#if CONFIG_LIBDRM
    case AV_PIX_FMT_DRM_PRIME:
        return vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    default:
        return vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}