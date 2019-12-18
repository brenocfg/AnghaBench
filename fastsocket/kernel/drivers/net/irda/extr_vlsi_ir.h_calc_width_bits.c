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
 int BAUD_BITS (unsigned int) ; 

__attribute__((used)) static inline unsigned
calc_width_bits(unsigned baudrate, unsigned widthselect, unsigned clockselect)
{
	unsigned	tmp;

	if (widthselect)	/* nominal 3/16 puls width */
		return (clockselect) ? 12 : 24;

	tmp = ((clockselect) ? 12 : 24) / (BAUD_BITS(baudrate)+1);

	/* intermediate result of integer division needed here */

	return (tmp>0) ? (tmp-1) : 0;
}