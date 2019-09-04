#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct devfsmount {int dummy; } ;
typedef  int /*<<< orphan*/  devnode_type_t ;
struct TYPE_9__ {struct devfsmount* dn_dvm; } ;
typedef  TYPE_1__ devnode_t ;
typedef  int /*<<< orphan*/  devdirent_t ;

/* Variables and functions */
 int dev_add_name (char const*,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int dev_add_node (int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__**,struct devfsmount*) ; 
 int /*<<< orphan*/  devfs_dn_free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 

int
dev_add_entry(const char *name, devnode_t * parent, int type, devnode_type_t * typeinfo,
	      devnode_t * proto, struct devfsmount *dvm, devdirent_t * *nm_pp)
{
	devnode_t *	dnp;
	int	error = 0;

	if ((error = dev_add_node(type, typeinfo, proto, &dnp, 
			(parent?parent->dn_dvm:dvm))) != 0)
	{
		printf("devfs: %s: base node allocation failed (Errno=%d)\n",
			name,error);
		return error;
	}
	if ((error = dev_add_name(name ,parent ,NULL, dnp, nm_pp)) != 0)
	{
		devfs_dn_free(dnp); /* 1->0 for dir, 0->(-1) for other */
		printf("devfs: %s: name slot allocation failed (Errno=%d)\n",
		       name,error);
		
	}
	return error;
}