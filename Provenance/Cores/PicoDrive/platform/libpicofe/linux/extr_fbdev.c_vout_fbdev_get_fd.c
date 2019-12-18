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
struct vout_fbdev {int fd; } ;

/* Variables and functions */

int vout_fbdev_get_fd(struct vout_fbdev *fbdev)
{
	return fbdev->fd;
}