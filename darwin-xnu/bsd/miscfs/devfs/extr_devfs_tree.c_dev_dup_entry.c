#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct devfsmount {int dummy; } ;
struct TYPE_11__ {TYPE_4__* dirlist; } ;
struct TYPE_12__ {TYPE_1__ Dir; } ;
struct TYPE_13__ {int dn_type; TYPE_2__ dn_typeinfo; struct devfsmount* dn_dvm; } ;
typedef  TYPE_3__ devnode_t ;
struct TYPE_14__ {char* de_name; TYPE_3__* de_dnp; struct TYPE_14__* de_next; } ;
typedef  TYPE_4__ devdirent_t ;

/* Variables and functions */
 int DEV_DIR ; 
 int ENOMEM ; 
 int dev_add_entry (char*,TYPE_3__*,int,int /*<<< orphan*/ *,TYPE_3__*,struct devfsmount*,TYPE_4__**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
dev_dup_entry(devnode_t * parent, devdirent_t * back, devdirent_t * *dnm_pp,
	      struct devfsmount *dvm)
{
	devdirent_t *	entry_p = NULL;
	devdirent_t *	newback;
	devdirent_t *	newfront;
	int	error;
	devnode_t *	dnp = back->de_dnp;
	int type = dnp->dn_type;

	/*
	 * go get the node made (if we need to)
	 * use the back one as a prototype
	 */
    error = dev_add_entry(back->de_name, parent, type, NULL, dnp,
                          parent?parent->dn_dvm:dvm, &entry_p);
    if (!error && (entry_p == NULL)) {
        error = ENOMEM; /* Really can't happen, but make static analyzer happy */
    }
	if (error != 0) {
		printf("duplicating %s failed\n",back->de_name);
        goto out;
	}

	/*
	 * If we have just made the root, then insert the pointer to the
	 * mount information
	 */
	if(dvm) {
		entry_p->de_dnp->dn_dvm = dvm;
	}

	/*
	 * If it is a directory, then recurse down all the other
	 * subnodes in it....
	 * note that this time we don't pass on the mount info..
	 */
	if (type == DEV_DIR)
	{
		for(newback = back->de_dnp->dn_typeinfo.Dir.dirlist;
				newback; newback = newback->de_next)
		{
			if((error = dev_dup_entry(entry_p->de_dnp,
					    newback, &newfront, NULL)) != 0)
			{
				break; /* back out with an error */
			}
		}
	}
out:
	*dnm_pp = entry_p;
	return error;
}