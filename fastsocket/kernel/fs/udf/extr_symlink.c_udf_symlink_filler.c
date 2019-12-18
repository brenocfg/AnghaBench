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
struct TYPE_4__ {char* i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenEAttr; TYPE_2__ i_ext; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {char* b_data; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_block_map (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_pc_to_char (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int udf_symlink_filler(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *bh = NULL;
	char *symlink;
	int err = -EIO;
	char *p = kmap(page);
	struct udf_inode_info *iinfo;

	lock_kernel();
	iinfo = UDF_I(inode);
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		symlink = iinfo->i_ext.i_data + iinfo->i_lenEAttr;
	} else {
		bh = sb_bread(inode->i_sb, udf_block_map(inode, 0));

		if (!bh)
			goto out;

		symlink = bh->b_data;
	}

	udf_pc_to_char(inode->i_sb, symlink, inode->i_size, p);
	brelse(bh);

	unlock_kernel();
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;

out:
	unlock_kernel();
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return err;
}