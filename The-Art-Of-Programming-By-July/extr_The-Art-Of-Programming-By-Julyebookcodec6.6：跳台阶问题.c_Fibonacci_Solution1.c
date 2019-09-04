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

long long Fibonacci_Solution1(unsigned int n)
{
	int result[2] = {0, 1, 2};
	if (n <= 2)
		return result[n];

	return Fibonacci_Solution1(n - 1) + Fibonacci_Solution1(n - 2);
}