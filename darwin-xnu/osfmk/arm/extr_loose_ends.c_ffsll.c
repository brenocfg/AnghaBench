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
 int __builtin_ctzll (unsigned long long) ; 

int
ffsll(unsigned long long mask)
{
	if (mask == 0)
		return 0;

	/*
	 * NOTE: cannot use __builtin_ffsll because it generates a call to
	 * 'ffsll'
	 */
	return 1 + __builtin_ctzll(mask);
}