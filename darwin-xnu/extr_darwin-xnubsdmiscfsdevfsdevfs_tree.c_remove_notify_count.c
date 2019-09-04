#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ dn_links; struct TYPE_3__* dn_nextsibling; } ;
typedef  TYPE_1__ devnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  devfs_nmountplanes ; 

__attribute__((used)) static uint32_t
remove_notify_count(devnode_t *dnp)
{
	uint32_t notify_count = 0;
	devnode_t *dnp2;

	/* 
	 * Could need to notify for one removed node on each mount and 
	 * one parent for each such node.
	 */
	notify_count = devfs_nmountplanes;
	notify_count += dnp->dn_links;	
	for (dnp2 = dnp->dn_nextsibling; dnp2 != dnp; dnp2 = dnp2->dn_nextsibling) {
		notify_count += dnp2->dn_links;	
	}

	return notify_count;

}