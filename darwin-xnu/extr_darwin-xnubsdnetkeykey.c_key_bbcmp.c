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
typedef  int u_int8_t ;
typedef  int u_int ;
typedef  int* caddr_t ;

/* Variables and functions */

__attribute__((used)) static int
key_bbcmp(
		  caddr_t p1,
		  caddr_t p2,
		  u_int bits)
{
	u_int8_t mask;
	
	/* XXX: This could be considerably faster if we compare a word
	 * at a time, but it is complicated on LSB Endian machines */
	
	/* Handle null pointers */
	if (p1 == NULL || p2 == NULL)
		return (p1 == p2);
	
	while (bits >= 8) {
		if (*p1++ != *p2++)
			return 0;
		bits -= 8;
	}
	
	if (bits > 0) {
		mask = ~((1<<(8-bits))-1);
		if ((*p1 & mask) != (*p2 & mask))
			return 0;
	}
	return 1;	/* Match! */
}