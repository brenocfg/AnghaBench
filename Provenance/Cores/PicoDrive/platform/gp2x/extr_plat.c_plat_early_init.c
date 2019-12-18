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
 int /*<<< orphan*/  gp2x_get_ticks_ms ; 
 int /*<<< orphan*/  gp2x_get_ticks_us ; 
 int /*<<< orphan*/  plat_get_ticks_ms_good ; 
 int /*<<< orphan*/  plat_get_ticks_us_good ; 

void plat_early_init(void)
{
	// just use gettimeofday until plat_init()
	gp2x_get_ticks_ms = plat_get_ticks_ms_good;
	gp2x_get_ticks_us = plat_get_ticks_us_good;
}