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
 int /*<<< orphan*/  set_ram_timing_vals (int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void set_ram_timings_(void)
{
	/* craigix: --cas 2 --trc 6 --tras 4 --twr 1 --tmrd 1 --trfc 1 --trp 2 --trcd 2 */
	set_ram_timing_vals(2, 6, 4, 1, 1, 1, 2, 2);
}