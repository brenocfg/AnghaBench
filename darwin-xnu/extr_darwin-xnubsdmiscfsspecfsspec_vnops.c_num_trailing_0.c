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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int /*<<< orphan*/  ISSET (int,int) ; 

int
num_trailing_0(uint64_t n)
{
	/*
	 * since in most cases the number of trailing 0s is very small,
	 * we simply counting sequentially from the lowest bit
	 */
	if (n == 0)
		return sizeof(n) * 8;
	int count = 0;
	while (!ISSET(n, 1)) {
		n >>= 1;
		++count;
	}
	return count;
}