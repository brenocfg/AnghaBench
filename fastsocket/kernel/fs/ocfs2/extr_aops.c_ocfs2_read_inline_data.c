#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id_data; } ;
struct TYPE_5__ {TYPE_1__ i_data; } ;
struct ocfs2_dinode {TYPE_2__ id2; int /*<<< orphan*/  i_dyn_features; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  KM_USER0 ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 scalar_t__ ocfs2_max_inline_data_with_xattr (int /*<<< orphan*/ ,struct ocfs2_dinode*) ; 

int ocfs2_read_inline_data(struct inode *inode, struct page *page,
			   struct buffer_head *di_bh)
{
	void *kaddr;
	loff_t size;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;

	if (!(le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_DATA_FL)) {
		ocfs2_error(inode->i_sb, "Inode %llu lost inline data flag",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno);
		return -EROFS;
	}

	size = i_size_read(inode);

	if (size > PAGE_CACHE_SIZE ||
	    size > ocfs2_max_inline_data_with_xattr(inode->i_sb, di)) {
		ocfs2_error(inode->i_sb,
			    "Inode %llu has with inline data has bad size: %Lu",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno,
			    (unsigned long long)size);
		return -EROFS;
	}

	kaddr = kmap_atomic(page, KM_USER0);
	if (size)
		memcpy(kaddr, di->id2.i_data.id_data, size);
	/* Clear the remaining part of the page */
	memset(kaddr + size, 0, PAGE_CACHE_SIZE - size);
	flush_dcache_page(page);
	kunmap_atomic(kaddr, KM_USER0);

	SetPageUptodate(page);

	return 0;
}