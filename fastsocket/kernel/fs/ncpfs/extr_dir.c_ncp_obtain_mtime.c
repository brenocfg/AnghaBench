#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct nw_info_struct {int /*<<< orphan*/  modifyDate; int /*<<< orphan*/  modifyTime; } ;
struct ncp_server {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  ncp_conn_valid (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_date_dos2unix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_is_server_root (struct inode*) ; 
 scalar_t__ ncp_obtain_info (struct ncp_server*,struct inode*,int /*<<< orphan*/ *,struct nw_info_struct*) ; 

__attribute__((used)) static time_t ncp_obtain_mtime(struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct ncp_server *server = NCP_SERVER(inode);
	struct nw_info_struct i;

	if (!ncp_conn_valid(server) || ncp_is_server_root(inode))
		return 0;

	if (ncp_obtain_info(server, inode, NULL, &i))
		return 0;

	return ncp_date_dos2unix(i.modifyTime, i.modifyDate);
}