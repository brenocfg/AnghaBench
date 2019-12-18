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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct vout_fbdev*) ; 
 int /*<<< orphan*/  vout_fbdev_release (struct vout_fbdev*) ; 

void vout_fbdev_finish(struct vout_fbdev *fbdev)
{
	vout_fbdev_release(fbdev);
	if (fbdev->fd >= 0)
		close(fbdev->fd);
	fbdev->fd = -1;
	free(fbdev);
}