#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_7__* dirlist; TYPE_3__* parent; TYPE_7__* myname; } ;
struct TYPE_14__ {TYPE_4__ Dir; } ;
struct TYPE_15__ {scalar_t__ dn_type; TYPE_5__ dn_typeinfo; } ;
typedef  TYPE_6__ devnode_t ;
struct TYPE_16__ {struct TYPE_16__* de_next; int /*<<< orphan*/  de_name; } ;
typedef  TYPE_7__ devdirent_t ;
struct TYPE_10__ {TYPE_7__* myname; } ;
struct TYPE_11__ {TYPE_1__ Dir; } ;
struct TYPE_12__ {TYPE_2__ dn_typeinfo; } ;

/* Variables and functions */
 scalar_t__ DEV_DIR ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

devdirent_t *
dev_findname(devnode_t * dir, const char *name)
{
	devdirent_t * newfp;
	if (dir->dn_type != DEV_DIR) return 0;/*XXX*/ /* printf?*/

	if (name[0] == '.')
	{
		if(name[1] == 0)
		{
			return dir->dn_typeinfo.Dir.myname;
		}
		if((name[1] == '.') && (name[2] == 0))
		{
			/* for root, .. == . */
			return dir->dn_typeinfo.Dir.parent->dn_typeinfo.Dir.myname;
		}
	}
	newfp = dir->dn_typeinfo.Dir.dirlist;

	while(newfp)
	{
		if(!(strncmp(name, newfp->de_name, sizeof(newfp->de_name))))
			return newfp;
		newfp = newfp->de_next;
	}
	return NULL;
}