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
typedef  int __u16 ;

/* Variables and functions */
 int find_next_bit (unsigned long*,int,int) ; 
 int find_next_zero_bit (unsigned long*,int,int) ; 

__attribute__((used)) static void sctp_tsnmap_find_gap_ack(unsigned long *map, __u16 off,
				     __u16 len, __u16 *start, __u16 *end)
{
	int i = off;

	/* Look through the entire array, but break out
	 * early if we have found the end of the Gap Ack Block.
	 */

	/* Also, stop looking past the maximum TSN seen. */

	/* Look for the start. */
	i = find_next_bit(map, len, off);
	if (i < len)
		*start = i;

	/* Look for the end.  */
	if (*start) {
		/* We have found the start, let's find the
		 * end.  If we find the end, break out.
		 */
		i = find_next_zero_bit(map, len, i);
		if (i < len)
			*end = i - 1;
	}
}