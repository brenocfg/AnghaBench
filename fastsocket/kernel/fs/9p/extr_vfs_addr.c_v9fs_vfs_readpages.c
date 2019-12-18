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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,...) ; 
 int read_cache_pages (struct address_space*,struct list_head*,void*,struct file*) ; 
 int v9fs_readpages_from_fscache (struct inode*,struct address_space*,struct list_head*,unsigned int*) ; 
 scalar_t__ v9fs_vfs_readpage ; 

__attribute__((used)) static int v9fs_vfs_readpages(struct file *filp, struct address_space *mapping,
			     struct list_head *pages, unsigned nr_pages)
{
	int ret = 0;
	struct inode *inode;

	inode = mapping->host;
	P9_DPRINTK(P9_DEBUG_VFS, "inode: %p file: %p\n", inode, filp);

	ret = v9fs_readpages_from_fscache(inode, mapping, pages, &nr_pages);
	if (ret == 0)
		return ret;

	ret = read_cache_pages(mapping, pages, (void *)v9fs_vfs_readpage, filp);
	P9_DPRINTK(P9_DEBUG_VFS, "  = %d\n", ret);
	return ret;
}