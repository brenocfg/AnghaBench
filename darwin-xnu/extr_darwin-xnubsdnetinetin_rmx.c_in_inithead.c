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
struct radix_node_head {int /*<<< orphan*/  rnh_close; int /*<<< orphan*/  rnh_matchaddr_args; int /*<<< orphan*/  rnh_matchaddr; int /*<<< orphan*/  rnh_deladdr; int /*<<< orphan*/  rnh_addaddr; } ;

/* Variables and functions */
 size_t AF_INET ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  in_addroute ; 
 int /*<<< orphan*/  in_clsroute ; 
 int /*<<< orphan*/  in_deleteroute ; 
 int /*<<< orphan*/  in_matroute ; 
 int /*<<< orphan*/  in_matroute_args ; 
 int /*<<< orphan*/  rn_inithead (void**,int) ; 
 int /*<<< orphan*/ * rt_tables ; 

int
in_inithead(void **head, int off)
{
	struct radix_node_head *rnh;

	/* If called from route_init(), make sure it is exactly once */
	VERIFY(head != (void **)&rt_tables[AF_INET] || *head == NULL);

	if (!rn_inithead(head, off))
		return (0);

	/*
	 * We can get here from nfs_subs.c as well, in which case this
	 * won't be for the real routing table and thus we're done;
	 * this also takes care of the case when we're called more than
	 * once from anywhere but route_init().
	 */
	if (head != (void **)&rt_tables[AF_INET])
		return (1);	/* only do this for the real routing table */

	rnh = *head;
	rnh->rnh_addaddr = in_addroute;
	rnh->rnh_deladdr = in_deleteroute;
	rnh->rnh_matchaddr = in_matroute;
	rnh->rnh_matchaddr_args = in_matroute_args;
	rnh->rnh_close = in_clsroute;
	return (1);
}