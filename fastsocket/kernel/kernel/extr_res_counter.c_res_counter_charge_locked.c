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
struct res_counter {scalar_t__ usage; scalar_t__ limit; scalar_t__ max_usage; int /*<<< orphan*/  failcnt; } ;

/* Variables and functions */
 int ENOMEM ; 

int res_counter_charge_locked(struct res_counter *counter, unsigned long val)
{
	if (counter->usage + val > counter->limit) {
		counter->failcnt++;
		return -ENOMEM;
	}

	counter->usage += val;
	if (counter->usage > counter->max_usage)
		counter->max_usage = counter->usage;
	return 0;
}