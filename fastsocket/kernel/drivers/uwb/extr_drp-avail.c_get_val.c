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
typedef  int /*<<< orphan*/  val ;
typedef  unsigned long u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static
unsigned long get_val(u8 *array, size_t itr, size_t len)
{
	unsigned long val = 0;
	size_t top = itr + len;

	BUG_ON(len > sizeof(val));

	while (itr < top) {
		val <<= 8;
		val |= array[top - 1];
		top--;
	}
	val <<= 8 * (sizeof(val) - len); /* padding */
	return val;
}