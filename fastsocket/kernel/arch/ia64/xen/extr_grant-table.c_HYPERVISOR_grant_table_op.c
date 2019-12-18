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
struct gnttab_map_grant_ref {int dummy; } ;

/* Variables and functions */
 unsigned int GNTTABOP_map_grant_ref ; 
 int /*<<< orphan*/  gnttab_map_grant_ref_pre (struct gnttab_map_grant_ref*) ; 
 int xencomm_hypercall_grant_table_op (unsigned int,void*,unsigned int) ; 

int
HYPERVISOR_grant_table_op(unsigned int cmd, void *uop, unsigned int count)
{
	if (cmd == GNTTABOP_map_grant_ref) {
		unsigned int i;
		for (i = 0; i < count; i++) {
			gnttab_map_grant_ref_pre(
				(struct gnttab_map_grant_ref *)uop + i);
		}
	}
	return xencomm_hypercall_grant_table_op(cmd, uop, count);
}