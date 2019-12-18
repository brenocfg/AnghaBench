#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  attributes; } ;
struct ncp_entry_info {TYPE_1__ i; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nwattr; int /*<<< orphan*/  opened; scalar_t__ flags; } ;

/* Variables and functions */
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_update_attrs (struct inode*,struct ncp_entry_info*) ; 
 int /*<<< orphan*/  ncp_update_dates (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  ncp_update_dirent (struct inode*,struct ncp_entry_info*) ; 

void ncp_update_inode2(struct inode* inode, struct ncp_entry_info *nwinfo)
{
	NCP_FINFO(inode)->flags = 0;
	if (!atomic_read(&NCP_FINFO(inode)->opened)) {
		NCP_FINFO(inode)->nwattr = nwinfo->i.attributes;
		ncp_update_attrs(inode, nwinfo);
	}

	ncp_update_dates(inode, &nwinfo->i);
	ncp_update_dirent(inode, nwinfo);
}