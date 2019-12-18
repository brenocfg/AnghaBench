#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  entrycount; TYPE_1__** dirlast; TYPE_4__* parent; scalar_t__ dirlist; } ;
struct TYPE_11__ {TYPE_2__ Dir; } ;
struct TYPE_12__ {scalar_t__ dn_type; int /*<<< orphan*/  dn_len; TYPE_3__ dn_typeinfo; TYPE_5__* dn_linklist; } ;
typedef  TYPE_4__ devnode_t ;
struct TYPE_13__ {int /*<<< orphan*/  de_name; TYPE_1__** de_prevp; TYPE_1__* de_next; struct TYPE_13__* de_nextlink; struct TYPE_13__** de_prevlinkp; TYPE_4__* de_dnp; TYPE_4__* de_parent; } ;
typedef  TYPE_5__ devdirent_t ;
struct TYPE_9__ {struct TYPE_9__** de_prevp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_DECR_ENTRIES () ; 
 scalar_t__ DEV_DIR ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  FREE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVFSNAME ; 
 int /*<<< orphan*/  devfs_dn_free (TYPE_4__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int
dev_free_name(devdirent_t * dirent_p)
{
	devnode_t *	parent = dirent_p->de_parent;
	devnode_t *	dnp = dirent_p->de_dnp;

	if(dnp) {
		if(dnp->dn_type == DEV_DIR)
		{
		    	devnode_t * p;

			if(dnp->dn_typeinfo.Dir.dirlist)
				return (ENOTEMPTY);
			p = dnp->dn_typeinfo.Dir.parent;
			devfs_dn_free(dnp); 	/* account for '.' */
			devfs_dn_free(p); 	/* '..' */
		}
		/*
		 * unlink us from the list of links for this node
		 * If we are the only link, it's easy!
		 * if we are a DIR of course there should not be any
		 * other links.
	 	 */
		if(dirent_p->de_nextlink == dirent_p) {
				dnp->dn_linklist = NULL;
		} else {
			if(dnp->dn_linklist == dirent_p) {
				dnp->dn_linklist = dirent_p->de_nextlink;
			}
		}
		devfs_dn_free(dnp);
	}
	
	dirent_p->de_nextlink->de_prevlinkp = dirent_p->de_prevlinkp;
	*(dirent_p->de_prevlinkp) = dirent_p->de_nextlink;

	/*
	 * unlink ourselves from the directory on this plane
	 */
	if(parent) /* if not fs root */
	{
		if( (*dirent_p->de_prevp = dirent_p->de_next) )/* yes, assign */
		{
			dirent_p->de_next->de_prevp = dirent_p->de_prevp;
		}
		else
		{
			parent->dn_typeinfo.Dir.dirlast
				= dirent_p->de_prevp;
		}
		parent->dn_typeinfo.Dir.entrycount--;
		parent->dn_len -= strlen(dirent_p->de_name) + 8;
	}

	DEVFS_DECR_ENTRIES();
	FREE(dirent_p, M_DEVFSNAME);
	return 0;
}