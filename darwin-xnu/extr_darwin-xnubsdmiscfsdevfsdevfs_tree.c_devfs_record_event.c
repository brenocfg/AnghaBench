#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ dn_vn; } ;
typedef  TYPE_1__ devnode_t ;
typedef  TYPE_2__* devfs_vnode_event_t ;
typedef  TYPE_3__* devfs_event_log_t ;
struct TYPE_8__ {size_t del_used; size_t del_max; TYPE_2__* del_entries; } ;
struct TYPE_7__ {scalar_t__ dve_vp; int /*<<< orphan*/  dve_events; int /*<<< orphan*/  dve_vid; } ;

/* Variables and functions */
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_ismonitored (scalar_t__) ; 
 int /*<<< orphan*/  vnode_vid (scalar_t__) ; 

__attribute__((used)) static void 
devfs_record_event(devfs_event_log_t delp, devnode_t *dnp, uint32_t events)
{
	if (delp->del_used >= delp->del_max) {
		panic("devfs event log overflowed.\n");
	}

	/* Can only notify for nodes that have an associated vnode */
	if (dnp->dn_vn != NULLVP && vnode_ismonitored(dnp->dn_vn)) {
		devfs_vnode_event_t dvep = &delp->del_entries[delp->del_used];
		dvep->dve_vp = dnp->dn_vn;
		dvep->dve_vid = vnode_vid(dnp->dn_vn);
		dvep->dve_events = events;
		delp->del_used++;
	}
}