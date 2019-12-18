#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpu_rate {long rate; scalar_t__ xtal; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {scalar_t__ rate; } ;

/* Variables and functions */
 long EINVAL ; 
 TYPE_1__ ck_ref ; 
 struct mpu_rate* rate_table ; 
 struct clk virtual_ck_mpu ; 

__attribute__((used)) static long omap1_round_to_table_rate(struct clk * clk, unsigned long rate)
{
	/* Find the highest supported frequency <= rate */
	struct mpu_rate * ptr;
	long  highest_rate;

	if (clk != &virtual_ck_mpu)
		return -EINVAL;

	highest_rate = -EINVAL;

	for (ptr = rate_table; ptr->rate; ptr++) {
		if (ptr->xtal != ck_ref.rate)
			continue;

		highest_rate = ptr->rate;

		/* Can check only after xtal frequency check */
		if (ptr->rate <= rate)
			break;
	}

	return highest_rate;
}