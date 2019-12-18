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
struct ati_remote {unsigned long acc_jiffies; scalar_t__ old_jiffies; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 

__attribute__((used)) static int ati_remote_compute_accel(struct ati_remote *ati_remote)
{
	static const char accel[] = { 1, 2, 4, 6, 9, 13, 20 };
	unsigned long now = jiffies;
	int acc;

	if (time_after(now, ati_remote->old_jiffies + msecs_to_jiffies(250))) {
		acc = 1;
		ati_remote->acc_jiffies = now;
	}
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(125)))
		acc = accel[0];
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(250)))
		acc = accel[1];
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(500)))
		acc = accel[2];
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(1000)))
		acc = accel[3];
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(1500)))
		acc = accel[4];
	else if (time_before(now, ati_remote->acc_jiffies + msecs_to_jiffies(2000)))
		acc = accel[5];
	else
		acc = accel[6];

	return acc;
}