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
typedef  scalar_t__ __u32 ;
typedef  int __u16 ;

/* Variables and functions */

__attribute__((used)) static inline int value_lower_bits(__u32 value, __u32 *array, int size, __u16 *field)
{
	int	i;
	__u16	mask = 0x1;
	__u16	result = 0x0;

	for (i=0; i < size; i++) {
		/* Add the current value to the bit field, shift mask */
		result |= mask;
		mask <<= 1;
		/* Finished ? */
		if (array[i] >= value)
			break;
	}
	/* Send back a valid index */
	if(i >= size)
	  i = size - 1;	/* Last item */
	*field = result;
	return i;
}