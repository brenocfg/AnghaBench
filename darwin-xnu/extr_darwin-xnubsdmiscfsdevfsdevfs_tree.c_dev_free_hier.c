#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* dirlist; } ;
struct TYPE_8__ {TYPE_1__ Dir; } ;
struct TYPE_9__ {scalar_t__ dn_type; TYPE_2__ dn_typeinfo; } ;
typedef  TYPE_3__ devnode_t ;
struct TYPE_10__ {TYPE_3__* de_dnp; } ;
typedef  TYPE_4__ devdirent_t ;

/* Variables and functions */
 scalar_t__ DEV_DIR ; 
 int /*<<< orphan*/  dev_free_name (TYPE_4__*) ; 

__attribute__((used)) static void
dev_free_hier(devdirent_t * dirent_p)
{
	devnode_t *	dnp = dirent_p->de_dnp;

	if(dnp) {
		if(dnp->dn_type == DEV_DIR)
		{
			while(dnp->dn_typeinfo.Dir.dirlist)
			{
				dev_free_hier(dnp->dn_typeinfo.Dir.dirlist);
				dev_free_name(dnp->dn_typeinfo.Dir.dirlist);
			}
		}
	}
}