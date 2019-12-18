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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 scalar_t__ atomic64_sub_return (scalar_t__,int /*<<< orphan*/ *) ; 

int atomic64_sub_and_test(u64 delta, atomic64_t *ptr)
{
	u64 new_val = atomic64_sub_return(delta, ptr);

	return new_val == 0;
}