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
struct page {TYPE_1__* mapping; } ;
struct inode {int i_size; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int efs_block_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EFS_BLOCKSIZE ; 
 int EIO ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  efs_bmap (struct inode*,int) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int efs_symlink_readpage(struct file *file, struct page *page)
{
	char *link = kmap(page);
	struct buffer_head * bh;
	struct inode * inode = page->mapping->host;
	efs_block_t size = inode->i_size;
	int err;
  
	err = -ENAMETOOLONG;
	if (size > 2 * EFS_BLOCKSIZE)
		goto fail;
  
	/* read first 512 bytes of link target */
	err = -EIO;
	bh = sb_bread(inode->i_sb, efs_bmap(inode, 0));
	if (!bh)
		goto fail;
	memcpy(link, bh->b_data, (size > EFS_BLOCKSIZE) ? EFS_BLOCKSIZE : size);
	brelse(bh);
	if (size > EFS_BLOCKSIZE) {
		bh = sb_bread(inode->i_sb, efs_bmap(inode, 1));
		if (!bh)
			goto fail;
		memcpy(link + EFS_BLOCKSIZE, bh->b_data, size - EFS_BLOCKSIZE);
		brelse(bh);
	}
	link[size] = '\0';
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;
fail:
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return err;
}