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
typedef  struct clk const clk ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int _clk_can_use_parent(const struct clk *clk_arr[], unsigned int size,
			       struct clk *parent)
{
	int i;

	for (i = 0; i < size; i++)
		if (parent == clk_arr[i])
			return i;

	return -EINVAL;
}