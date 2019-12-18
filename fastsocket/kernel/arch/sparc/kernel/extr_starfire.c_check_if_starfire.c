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
 int prom_finddevice (char*) ; 
 int this_is_starfire ; 

void check_if_starfire(void)
{
	int ssnode = prom_finddevice("/ssp-serial");
	if (ssnode != 0 && ssnode != -1)
		this_is_starfire = 1;
}