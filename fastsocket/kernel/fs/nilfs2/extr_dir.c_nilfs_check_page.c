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
struct super_block {int dummy; } ;
struct page {unsigned int index; TYPE_1__* mapping; } ;
struct nilfs_dir_entry {int name_len; int /*<<< orphan*/  inode; int /*<<< orphan*/  rec_len; } ;
struct inode {unsigned int i_size; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 unsigned int NILFS_DIR_REC_LEN (int) ; 
 unsigned int PAGE_CACHE_MASK ; 
 unsigned int PAGE_CACHE_SHIFT ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int nilfs_chunk_size (struct inode*) ; 
 int /*<<< orphan*/  nilfs_error (struct super_block*,char*,char*,int /*<<< orphan*/ ,...) ; 
 char* page_address (struct page*) ; 

__attribute__((used)) static void nilfs_check_page(struct page *page)
{
	struct inode *dir = page->mapping->host;
	struct super_block *sb = dir->i_sb;
	unsigned chunk_size = nilfs_chunk_size(dir);
	char *kaddr = page_address(page);
	unsigned offs, rec_len;
	unsigned limit = PAGE_CACHE_SIZE;
	struct nilfs_dir_entry *p;
	char *error;

	if ((dir->i_size >> PAGE_CACHE_SHIFT) == page->index) {
		limit = dir->i_size & ~PAGE_CACHE_MASK;
		if (limit & (chunk_size - 1))
			goto Ebadsize;
		if (!limit)
			goto out;
	}
	for (offs = 0; offs <= limit - NILFS_DIR_REC_LEN(1); offs += rec_len) {
		p = (struct nilfs_dir_entry *)(kaddr + offs);
		rec_len = le16_to_cpu(p->rec_len);

		if (rec_len < NILFS_DIR_REC_LEN(1))
			goto Eshort;
		if (rec_len & 3)
			goto Ealign;
		if (rec_len < NILFS_DIR_REC_LEN(p->name_len))
			goto Enamelen;
		if (((offs + rec_len - 1) ^ offs) & ~(chunk_size-1))
			goto Espan;
	}
	if (offs != limit)
		goto Eend;
out:
	SetPageChecked(page);
	return;

	/* Too bad, we had an error */

Ebadsize:
	nilfs_error(sb, "nilfs_check_page",
		    "size of directory #%lu is not a multiple of chunk size",
		    dir->i_ino
	);
	goto fail;
Eshort:
	error = "rec_len is smaller than minimal";
	goto bad_entry;
Ealign:
	error = "unaligned directory entry";
	goto bad_entry;
Enamelen:
	error = "rec_len is too small for name_len";
	goto bad_entry;
Espan:
	error = "directory entry across blocks";
bad_entry:
	nilfs_error(sb, "nilfs_check_page", "bad entry in directory #%lu: %s - "
		    "offset=%lu, inode=%lu, rec_len=%d, name_len=%d",
		    dir->i_ino, error, (page->index<<PAGE_CACHE_SHIFT)+offs,
		    (unsigned long) le64_to_cpu(p->inode),
		    rec_len, p->name_len);
	goto fail;
Eend:
	p = (struct nilfs_dir_entry *)(kaddr + offs);
	nilfs_error(sb, "nilfs_check_page",
		    "entry in directory #%lu spans the page boundary"
		    "offset=%lu, inode=%lu",
		    dir->i_ino, (page->index<<PAGE_CACHE_SHIFT)+offs,
		    (unsigned long) le64_to_cpu(p->inode));
fail:
	SetPageChecked(page);
	SetPageError(page);
}