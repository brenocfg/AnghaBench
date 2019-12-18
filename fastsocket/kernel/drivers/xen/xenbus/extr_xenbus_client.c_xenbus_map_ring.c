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
struct xenbus_device {int /*<<< orphan*/  otherend_id; } ;
struct gnttab_map_grant_ref {unsigned long host_addr; int ref; scalar_t__ status; int /*<<< orphan*/  handle; int /*<<< orphan*/  dom; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  grant_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 scalar_t__ GNTST_okay ; 
 int /*<<< orphan*/  GNTTABOP_map_grant_ref ; 
 scalar_t__ HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_map_grant_ref*,int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,scalar_t__,char*,int,int /*<<< orphan*/ ) ; 

int xenbus_map_ring(struct xenbus_device *dev, int gnt_ref,
		    grant_handle_t *handle, void *vaddr)
{
	struct gnttab_map_grant_ref op = {
		.host_addr = (unsigned long)vaddr,
		.flags     = GNTMAP_host_map,
		.ref       = gnt_ref,
		.dom       = dev->otherend_id,
	};

	if (HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, &op, 1))
		BUG();

	if (op.status != GNTST_okay) {
		xenbus_dev_fatal(dev, op.status,
				 "mapping in shared page %d from domain %d",
				 gnt_ref, dev->otherend_id);
	} else
		*handle = op.handle;

	return op.status;
}