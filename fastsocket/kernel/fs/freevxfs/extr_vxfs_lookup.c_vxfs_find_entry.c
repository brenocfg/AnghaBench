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
typedef  scalar_t__ u_long ;
struct vxfs_direct {int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_reclen; } ;
struct vxfs_dirblk {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; TYPE_2__* i_sb; } ;
struct TYPE_3__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ VXFS_BLOCK_PER_PAGE (TYPE_2__*) ; 
 scalar_t__ VXFS_DIRBLKOV (struct vxfs_dirblk*) ; 
 scalar_t__ VXFS_DIRLEN (int) ; 
 scalar_t__ dir_blocks (struct inode*) ; 
 scalar_t__ dir_pages (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* vxfs_get_page (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vxfs_match (int,char const*,struct vxfs_direct*) ; 
 struct vxfs_direct* vxfs_next_entry (struct vxfs_direct*) ; 
 int /*<<< orphan*/  vxfs_put_page (struct page*) ; 

__attribute__((used)) static struct vxfs_direct *
vxfs_find_entry(struct inode *ip, struct dentry *dp, struct page **ppp)
{
	u_long				npages, page, nblocks, pblocks, block;
	u_long				bsize = ip->i_sb->s_blocksize;
	const char			*name = dp->d_name.name;
	int				namelen = dp->d_name.len;

	npages = dir_pages(ip);
	nblocks = dir_blocks(ip);
	pblocks = VXFS_BLOCK_PER_PAGE(ip->i_sb);
	
	for (page = 0; page < npages; page++) {
		caddr_t			kaddr;
		struct page		*pp;

		pp = vxfs_get_page(ip->i_mapping, page);
		if (IS_ERR(pp))
			continue;
		kaddr = (caddr_t)page_address(pp);

		for (block = 0; block <= nblocks && block <= pblocks; block++) {
			caddr_t			baddr, limit;
			struct vxfs_dirblk	*dbp;
			struct vxfs_direct	*de;

			baddr = kaddr + (block * bsize);
			limit = baddr + bsize - VXFS_DIRLEN(1);
			
			dbp = (struct vxfs_dirblk *)baddr;
			de = (struct vxfs_direct *)(baddr + VXFS_DIRBLKOV(dbp));

			for (; (caddr_t)de <= limit; de = vxfs_next_entry(de)) {
				if (!de->d_reclen)
					break;
				if (!de->d_ino)
					continue;
				if (vxfs_match(namelen, name, de)) {
					*ppp = pp;
					return (de);
				}
			}
		}
		vxfs_put_page(pp);
	}

	return NULL;
}