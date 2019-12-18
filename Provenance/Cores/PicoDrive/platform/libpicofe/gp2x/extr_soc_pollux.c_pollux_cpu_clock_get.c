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
 int decode_pll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memregl ; 

__attribute__((used)) static int pollux_cpu_clock_get(void)
{
	return decode_pll(memregl[0xf004>>2]) / 1000000;
}