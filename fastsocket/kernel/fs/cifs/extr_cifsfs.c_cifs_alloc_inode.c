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
struct super_block {int dummy; } ;
struct inode {int i_blkbits; } ;
struct cifsInodeInfo {int cifsAttrs; int delete_pending; int invalid_mapping; struct inode vfs_inode; int /*<<< orphan*/  openFileList; scalar_t__ server_eof; scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_inode_cachep ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int /*<<< orphan*/ ) ; 
 struct cifsInodeInfo* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *
cifs_alloc_inode(struct super_block *sb)
{
	struct cifsInodeInfo *cifs_inode;
	cifs_inode = kmem_cache_alloc(cifs_inode_cachep, GFP_KERNEL);
	if (!cifs_inode)
		return NULL;
	cifs_inode->cifsAttrs = 0x20;	/* default */
	cifs_inode->time = 0;
	/* Until the file is open and we have gotten oplock
	info back from the server, can not assume caching of
	file data or metadata */
	cifs_set_oplock_level(cifs_inode, 0);
	cifs_inode->delete_pending = false;
	cifs_inode->invalid_mapping = false;
	cifs_inode->vfs_inode.i_blkbits = 14;  /* 2**14 = CIFS_MAX_MSGSIZE */
	cifs_inode->server_eof = 0;

	/* Can not set i_flags here - they get immediately overwritten
	   to zero by the VFS */
/*	cifs_inode->vfs_inode.i_flags = S_NOATIME | S_NOCMTIME;*/
	INIT_LIST_HEAD(&cifs_inode->openFileList);
	return &cifs_inode->vfs_inode;
}