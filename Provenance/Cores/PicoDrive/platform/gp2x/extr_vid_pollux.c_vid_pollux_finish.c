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

/* Variables and functions */
 int /*<<< orphan*/  FB_MEM_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int fbdev ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vid_pollux_finish(void)
{
	memset(gp2x_screens[0], 0, FB_MEM_SIZE);
	munmap(gp2x_screens[0], FB_MEM_SIZE);
	close(fbdev);
	fbdev = -1;
}