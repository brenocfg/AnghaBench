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
struct super_block {struct dentry* s_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  mounted_vol; } ;
struct ncp_server {TYPE_1__ m; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __name ;
typedef  void* __le32 ;
struct TYPE_4__ {void* DosDirNum; void* dirEntNum; int /*<<< orphan*/  volNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENOENT ; 
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  NCP_MAXPATHLEN ; 
 struct ncp_server* NCP_SBP (struct super_block*) ; 
 int /*<<< orphan*/  PPRINTK (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_get_volume_root (struct ncp_server*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void**) ; 
 int ncp_io2vol (struct ncp_server*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ncp_single_volume (struct ncp_server*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int ncp_conn_logged_in(struct super_block *sb)
{
	struct ncp_server* server = NCP_SBP(sb);
	int result;

	if (ncp_single_volume(server)) {
		int len;
		struct dentry* dent;
		__u32 volNumber;
		__le32 dirEntNum;
		__le32 DosDirNum;
		__u8 __name[NCP_MAXPATHLEN + 1];

		len = sizeof(__name);
		result = ncp_io2vol(server, __name, &len, server->m.mounted_vol,
				    strlen(server->m.mounted_vol), 1);
		if (result)
			goto out;
		result = -ENOENT;
		if (ncp_get_volume_root(server, __name, &volNumber, &dirEntNum, &DosDirNum)) {
			PPRINTK("ncp_conn_logged_in: %s not found\n",
				server->m.mounted_vol);
			goto out;
		}
		dent = sb->s_root;
		if (dent) {
			struct inode* ino = dent->d_inode;
			if (ino) {
				NCP_FINFO(ino)->volNumber = volNumber;
				NCP_FINFO(ino)->dirEntNum = dirEntNum;
				NCP_FINFO(ino)->DosDirNum = DosDirNum;
			} else {
				DPRINTK("ncpfs: sb->s_root->d_inode == NULL!\n");
			}
		} else {
			DPRINTK("ncpfs: sb->s_root == NULL!\n");
		}
	}
	result = 0;

out:
	return result;
}