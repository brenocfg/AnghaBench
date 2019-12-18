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
typedef  int u_int32_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool
necp_buffer_compare_with_bit_prefix(u_int8_t *p1, u_int8_t *p2, u_int32_t bits)
{
	u_int8_t mask;

	/* Handle null pointers */
	if (p1 == NULL || p2 == NULL) {
		return (p1 == p2);
	}

	while (bits >= 8) {
		if (*p1++ != *p2++) {
			return (FALSE);
		}
		bits -= 8;
	}

	if (bits > 0) {
		mask = ~((1<<(8-bits))-1);
		if ((*p1 & mask) != (*p2 & mask)) {
			return (FALSE);
		}
	}
	return (TRUE);
}