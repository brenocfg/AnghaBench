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
 int /*<<< orphan*/ * linux_lvl14 ; 
 int /*<<< orphan*/ * lvl14_save ; 

void install_linux_ticker(void)
{

	if (!linux_lvl14)
		return;
	linux_lvl14[0] =  lvl14_save[0];
	linux_lvl14[1] =  lvl14_save[1];
	linux_lvl14[2] =  lvl14_save[2];
	linux_lvl14[3] =  lvl14_save[3];
}