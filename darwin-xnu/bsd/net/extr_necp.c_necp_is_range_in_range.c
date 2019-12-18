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
necp_is_range_in_range(struct sockaddr *inner_range_start, struct sockaddr *inner_range_end, struct sockaddr *range_start, struct sockaddr *range_end)
{
	int cmp = 0;

	if (inner_range_start == NULL || inner_range_end == NULL || range_start == NULL || range_end == NULL) {
		return (FALSE);
	}

	/* Must be greater than or equal to start */
	cmp = necp_addr_compare(inner_range_start, range_start, 1);
	if (cmp != 0 && cmp != 1) {
		return (FALSE);
	}

	/* Must be less than or equal to end */
	cmp = necp_addr_compare(inner_range_end, range_end, 1);
	if (cmp != 0 && cmp != -1) {
		return (FALSE);
	}

	return (TRUE);
}