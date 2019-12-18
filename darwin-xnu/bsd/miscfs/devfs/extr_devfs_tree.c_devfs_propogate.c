#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int dn_type; int /*<<< orphan*/  dn_dvm; struct TYPE_9__* dn_nextsibling; } ;
typedef  TYPE_1__ devnode_t ;
typedef  int /*<<< orphan*/ * devfs_event_log_t ;
struct TYPE_10__ {char* de_name; TYPE_1__* de_dnp; } ;
typedef  TYPE_2__ devdirent_t ;

/* Variables and functions */
 scalar_t__ DEV_DIR ; 
 int /*<<< orphan*/  VNODE_EVENT_DIR_CREATED ; 
 int /*<<< orphan*/  VNODE_EVENT_FILE_CREATED ; 
 int /*<<< orphan*/  VNODE_EVENT_LINK ; 
 int dev_add_entry (char*,TYPE_1__*,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  devfs_record_event (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
devfs_propogate(devdirent_t * parent,devdirent_t * child, devfs_event_log_t delp)
{
	int	error;
	devdirent_t * newnmp;
	devnode_t *	dnp = child->de_dnp;
	devnode_t *	pdnp = parent->de_dnp;
	devnode_t *	adnp = parent->de_dnp;
	int type = child->de_dnp->dn_type;
	uint32_t events;
	
	events = (dnp->dn_type == DEV_DIR ? VNODE_EVENT_DIR_CREATED : VNODE_EVENT_FILE_CREATED);
	if (delp != NULL) {
		devfs_record_event(delp, pdnp, events);
	}

	/***********************************************
	 * Find the other instances of the parent node
	 ***********************************************/
	for (adnp = pdnp->dn_nextsibling;
		adnp != pdnp;
		adnp = adnp->dn_nextsibling)
	{
		/*
		 * Make the node, using the original as a prototype)
		 * if the node already exists on that plane it won't be
		 * re-made..
		 */
		if ((error = dev_add_entry(child->de_name, adnp, type,
					   NULL, dnp, adnp->dn_dvm, 
					   &newnmp)) != 0) {
			printf("duplicating %s failed\n",child->de_name);
		} else {
			if (delp != NULL) {
				devfs_record_event(delp, adnp, events);

				/* 
				 * Slightly subtle.  We're guaranteed that there will
				 * only be a vnode hooked into this devnode if we're creating
				 * a new link to an existing node; otherwise, the devnode is new
				 * and no one can have looked it up yet. If we're making a link,
				 * then the buffer is large enough for two nodes in each 
				 * plane; otherwise, there's no vnode and this call will
				 * do nothing.
				 */
				devfs_record_event(delp, newnmp->de_dnp, VNODE_EVENT_LINK);
			}
		}
	}
	return 0;	/* for now always succeed */
}