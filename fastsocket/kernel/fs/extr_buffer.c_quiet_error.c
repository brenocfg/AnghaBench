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
struct buffer_head {int /*<<< orphan*/  b_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Quiet ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int quiet_error(struct buffer_head *bh)
{
	if (!test_bit(BH_Quiet, &bh->b_state) && printk_ratelimit())
		return 0;
	return 1;
}