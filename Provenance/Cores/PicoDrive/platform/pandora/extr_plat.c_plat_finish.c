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
 int /*<<< orphan*/  main_fb ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vout_fbdev_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenv_finish () ; 

void plat_finish(void)
{
	vout_fbdev_finish(main_fb);
	xenv_finish();

	printf("all done\n");
}