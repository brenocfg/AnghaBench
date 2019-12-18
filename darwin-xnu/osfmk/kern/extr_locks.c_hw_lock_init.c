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
typedef  int /*<<< orphan*/  hw_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ordered_store_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
hw_lock_init(hw_lock_t lock)
{
	ordered_store_hw(lock, 0);
}