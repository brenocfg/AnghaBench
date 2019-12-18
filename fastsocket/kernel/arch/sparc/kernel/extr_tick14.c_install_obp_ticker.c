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
 int /*<<< orphan*/ * obp_lvl14 ; 

void install_obp_ticker(void)
{

	if (!linux_lvl14)
		return;
	linux_lvl14[0] =  obp_lvl14[0];
	linux_lvl14[1] =  obp_lvl14[1];
	linux_lvl14[2] =  obp_lvl14[2];
	linux_lvl14[3] =  obp_lvl14[3]; 
}