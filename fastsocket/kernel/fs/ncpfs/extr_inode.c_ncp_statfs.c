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
struct super_block {struct dentry* s_root; } ;
struct ncp_volume_info {int sectors_per_block; int /*<<< orphan*/  available_dir_entries; int /*<<< orphan*/  total_dir_entries; int /*<<< orphan*/  free_blocks; int /*<<< orphan*/  total_blocks; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mounted_vol; } ;
struct ncp_server {TYPE_1__ m; } ;
struct ncp_inode_info {int /*<<< orphan*/  DosDirNum; int /*<<< orphan*/  volNumber; } ;
struct kstatfs {int f_bsize; int f_namelen; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; void* f_type; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; struct super_block* d_sb; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int NCP_BLOCK_SIZE ; 
 struct ncp_inode_info* NCP_FINFO (struct inode*) ; 
 struct ncp_server* NCP_SBP (struct super_block*) ; 
 void* NCP_SUPER_MAGIC ; 
 int ncp_dirhandle_alloc (struct ncp_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_dirhandle_free (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int ncp_get_directory_info (struct ncp_server*,int /*<<< orphan*/ ,struct ncp_volume_info*) ; 

__attribute__((used)) static int ncp_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct dentry* d;
	struct inode* i;
	struct ncp_inode_info* ni;
	struct ncp_server* s;
	struct ncp_volume_info vi;
	struct super_block *sb = dentry->d_sb;
	int err;
	__u8 dh;
	
	d = sb->s_root;
	if (!d) {
		goto dflt;
	}
	i = d->d_inode;
	if (!i) {
		goto dflt;
	}
	ni = NCP_FINFO(i);
	if (!ni) {
		goto dflt;
	}
	s = NCP_SBP(sb);
	if (!s) {
		goto dflt;
	}
	if (!s->m.mounted_vol[0]) {
		goto dflt;
	}

	err = ncp_dirhandle_alloc(s, ni->volNumber, ni->DosDirNum, &dh);
	if (err) {
		goto dflt;
	}
	err = ncp_get_directory_info(s, dh, &vi);
	ncp_dirhandle_free(s, dh);
	if (err) {
		goto dflt;
	}
	buf->f_type = NCP_SUPER_MAGIC;
	buf->f_bsize = vi.sectors_per_block * 512;
	buf->f_blocks = vi.total_blocks;
	buf->f_bfree = vi.free_blocks;
	buf->f_bavail = vi.free_blocks;
	buf->f_files = vi.total_dir_entries;
	buf->f_ffree = vi.available_dir_entries;
	buf->f_namelen = 12;
	return 0;

	/* We cannot say how much disk space is left on a mounted
	   NetWare Server, because free space is distributed over
	   volumes, and the current user might have disk quotas. So
	   free space is not that simple to determine. Our decision
	   here is to err conservatively. */

dflt:;
	buf->f_type = NCP_SUPER_MAGIC;
	buf->f_bsize = NCP_BLOCK_SIZE;
	buf->f_blocks = 0;
	buf->f_bfree = 0;
	buf->f_bavail = 0;
	buf->f_namelen = 12;
	return 0;
}