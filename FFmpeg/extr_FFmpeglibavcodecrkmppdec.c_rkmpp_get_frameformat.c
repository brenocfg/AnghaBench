#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int MppFrameFormat ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_NV12 ; 
#define  MPP_FMT_YUV420SP 128 

__attribute__((used)) static uint32_t rkmpp_get_frameformat(MppFrameFormat mppformat)
{
    switch (mppformat) {
    case MPP_FMT_YUV420SP:          return DRM_FORMAT_NV12;
#ifdef DRM_FORMAT_NV12_10
    case MPP_FMT_YUV420SP_10BIT:    return DRM_FORMAT_NV12_10;
#endif
    default:                        return 0;
    }
}