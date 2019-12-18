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
 int /*<<< orphan*/  lasat_ndelay (int) ; 
 int /*<<< orphan*/  rtc_nrst_low () ; 

__attribute__((used)) static void rtc_end_op(void)
{
	rtc_nrst_low();
	lasat_ndelay(1000);
}