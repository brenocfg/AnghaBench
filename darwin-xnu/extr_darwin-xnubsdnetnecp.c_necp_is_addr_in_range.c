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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int necp_addr_compare (struct sockaddr*,struct sockaddr*,int) ; 

__attribute__((used)) static bool
necp_is_addr_in_range(struct sockaddr *addr, struct sockaddr *range_start, struct sockaddr *range_end)
{
	int cmp = 0;

	if (addr == NULL || range_start == NULL || range_end == NULL) {
		return (FALSE);
	}

	/* Must be greater than or equal to start */
	cmp = necp_addr_compare(addr, range_start, 1);
	if (cmp != 0 && cmp != 1) {
		return (FALSE);
	}

	/* Must be less than or equal to end */
	cmp = necp_addr_compare(addr, range_end, 1);
	if (cmp != 0 && cmp != -1) {
		return (FALSE);
	}

	return (TRUE);
}