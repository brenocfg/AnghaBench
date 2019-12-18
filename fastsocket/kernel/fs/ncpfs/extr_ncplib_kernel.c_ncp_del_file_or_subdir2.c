#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ncp_server {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  DosDirNum; int /*<<< orphan*/  volNumber; } ;

/* Variables and functions */
 TYPE_1__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  NW_NS_DOS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ncp_DeleteNSEntry (struct ncp_server*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ncp_del_file_or_subdir2(struct ncp_server *server,
			struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	__u8  volnum;
	__le32 dirent;

	if (!inode) {
		return 0xFF;	/* Any error */
	}
	volnum = NCP_FINFO(inode)->volNumber;
	dirent = NCP_FINFO(inode)->DosDirNum;
	return ncp_DeleteNSEntry(server, 1, volnum, dirent, NULL, NW_NS_DOS, cpu_to_le16(0x8006));
}