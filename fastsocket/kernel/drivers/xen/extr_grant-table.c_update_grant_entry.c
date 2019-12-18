#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;
struct TYPE_2__ {unsigned long frame; unsigned int flags; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 TYPE_1__* shared ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void update_grant_entry(grant_ref_t ref, domid_t domid,
			       unsigned long frame, unsigned flags)
{
	/*
	 * Introducing a valid entry into the grant table:
	 *  1. Write ent->domid.
	 *  2. Write ent->frame:
	 *      GTF_permit_access:   Frame to which access is permitted.
	 *      GTF_accept_transfer: Pseudo-phys frame slot being filled by new
	 *                           frame, or zero if none.
	 *  3. Write memory barrier (WMB).
	 *  4. Write ent->flags, inc. valid type.
	 */
	shared[ref].frame = frame;
	shared[ref].domid = domid;
	wmb();
	shared[ref].flags = flags;
}