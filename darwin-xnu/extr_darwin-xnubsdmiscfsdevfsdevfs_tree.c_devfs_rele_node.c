#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dn_refcount; int dn_lflags; } ;
typedef  TYPE_1__ devnode_t ;

/* Variables and functions */
 int DN_DELETE ; 
 int /*<<< orphan*/  devnode_free (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void 
devfs_rele_node(devnode_t *dnp)
{
	dnp->dn_refcount--;
	if (dnp->dn_refcount < 0) {
		panic("devfs_rele_node: devnode with a negative refcount!\n");
	} else if ((dnp->dn_refcount == 0) && (dnp->dn_lflags & DN_DELETE))  {
		devnode_free(dnp);
	}

}