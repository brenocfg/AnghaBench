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
struct TYPE_3__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ncp_server {TYPE_1__ m; } ;
struct ncp_entry_info {int /*<<< orphan*/  i; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTK (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  ncp_update_attrs (struct inode*,struct ncp_entry_info*) ; 
 int /*<<< orphan*/  ncp_update_dates (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_update_inode (struct inode*,struct ncp_entry_info*) ; 

__attribute__((used)) static void ncp_set_attr(struct inode *inode, struct ncp_entry_info *nwinfo)
{
	struct ncp_server *server = NCP_SERVER(inode);

	NCP_FINFO(inode)->flags = 0;
	
	ncp_update_attrs(inode, nwinfo);

	DDPRINTK("ncp_read_inode: inode->i_mode = %u\n", inode->i_mode);

	inode->i_nlink = 1;
	inode->i_uid = server->m.uid;
	inode->i_gid = server->m.gid;

	ncp_update_dates(inode, &nwinfo->i);
	ncp_update_inode(inode, nwinfo);
}