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
struct TYPE_3__ {int /*<<< orphan*/  entryName; int /*<<< orphan*/  attributes; } ;
struct ncp_entry_info {TYPE_1__ i; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  access; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirEntNum; int /*<<< orphan*/  volNumber; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  access; int /*<<< orphan*/  nwattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_update_dirent (struct inode*,struct ncp_entry_info*) ; 

void ncp_update_inode(struct inode *inode, struct ncp_entry_info *nwinfo)
{
	ncp_update_dirent(inode, nwinfo);
	NCP_FINFO(inode)->nwattr = nwinfo->i.attributes;
	NCP_FINFO(inode)->access = nwinfo->access;
	memcpy(NCP_FINFO(inode)->file_handle, nwinfo->file_handle,
			sizeof(nwinfo->file_handle));
	DPRINTK("ncp_update_inode: updated %s, volnum=%d, dirent=%u\n",
		nwinfo->i.entryName, NCP_FINFO(inode)->volNumber,
		NCP_FINFO(inode)->dirEntNum);
}