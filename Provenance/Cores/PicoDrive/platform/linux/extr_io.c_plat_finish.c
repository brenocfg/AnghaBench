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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int /*<<< orphan*/  vout_fbdev_finish () ; 

void plat_finish(void)
{
#ifdef FBDEV
	vout_fbdev_finish();
#else
	free(g_screen_ptr);
#endif
}