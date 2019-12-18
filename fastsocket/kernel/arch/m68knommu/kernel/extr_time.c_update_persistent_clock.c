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
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int set_rtc_mmss (int /*<<< orphan*/ ) ; 

int update_persistent_clock(struct timespec now)
{
	return set_rtc_mmss(now.tv_sec);
}