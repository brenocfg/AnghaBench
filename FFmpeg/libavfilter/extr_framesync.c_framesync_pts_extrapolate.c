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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  FFFrameSync ;

/* Variables and functions */

__attribute__((used)) static int64_t framesync_pts_extrapolate(FFFrameSync *fs, unsigned in,
                                         int64_t pts)
{
    /* Possible enhancement: use the link's frame rate */
    return pts + 1;
}