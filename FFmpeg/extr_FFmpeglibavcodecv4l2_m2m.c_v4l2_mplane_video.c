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
struct v4l2_capability {int capabilities; } ;

/* Variables and functions */
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int V4L2_CAP_VIDEO_OUTPUT_MPLANE ; 

__attribute__((used)) static inline int v4l2_mplane_video(struct v4l2_capability *cap)
{
    if (cap->capabilities & (V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_VIDEO_OUTPUT_MPLANE) &&
        cap->capabilities & V4L2_CAP_STREAMING)
        return 1;

    if (cap->capabilities & V4L2_CAP_VIDEO_M2M_MPLANE)
        return 1;

    return 0;
}