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
struct video_device {int current_norm; } ;

/* Variables and functions */
 int LINE_SZ_4CIFS_NTSC ; 
 int LINE_SZ_4CIFS_PAL ; 
 int V4L2_STD_NTSC ; 

__attribute__((used)) static int norm_maxw(struct video_device *vdev)
{
	return (vdev->current_norm & V4L2_STD_NTSC) ?
	    LINE_SZ_4CIFS_NTSC : LINE_SZ_4CIFS_PAL;
}