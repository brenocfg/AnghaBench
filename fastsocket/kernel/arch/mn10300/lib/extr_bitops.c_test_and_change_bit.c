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
 scalar_t__ test_and_clear_bit (int,void volatile*) ; 
 int /*<<< orphan*/  test_and_set_bit (int,void volatile*) ; 
 scalar_t__ test_bit (int,void volatile*) ; 

int test_and_change_bit(int nr, volatile void *addr)
{
	if (test_bit(nr, addr))
		goto try_clear_bit;

try_set_bit:
	if (!test_and_set_bit(nr, addr))
		return 0;

try_clear_bit:
	if (test_and_clear_bit(nr, addr))
		return 1;

	goto try_set_bit;
}