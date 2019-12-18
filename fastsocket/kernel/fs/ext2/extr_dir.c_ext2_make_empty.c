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
struct page {int /*<<< orphan*/  mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; struct address_space* i_mapping; } ;
struct ext2_dir_entry_2 {int name_len; int /*<<< orphan*/  name; void* inode; void* rec_len; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EXT2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int __ext2_write_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 unsigned int ext2_chunk_size (struct inode*) ; 
 int ext2_commit_chunk (struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 void* ext2_rec_len_to_disk (int) ; 
 int /*<<< orphan*/  ext2_set_de_type (struct ext2_dir_entry_2*,struct inode*) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int ext2_make_empty(struct inode *inode, struct inode *parent)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page = grab_cache_page(mapping, 0);
	unsigned chunk_size = ext2_chunk_size(inode);
	struct ext2_dir_entry_2 * de;
	int err;
	void *kaddr;

	if (!page)
		return -ENOMEM;

	err = __ext2_write_begin(NULL, page->mapping, 0, chunk_size, 0,
							&page, NULL);
	if (err) {
		unlock_page(page);
		goto fail;
	}
	kaddr = kmap_atomic(page, KM_USER0);
	memset(kaddr, 0, chunk_size);
	de = (struct ext2_dir_entry_2 *)kaddr;
	de->name_len = 1;
	de->rec_len = ext2_rec_len_to_disk(EXT2_DIR_REC_LEN(1));
	memcpy (de->name, ".\0\0", 4);
	de->inode = cpu_to_le32(inode->i_ino);
	ext2_set_de_type (de, inode);

	de = (struct ext2_dir_entry_2 *)(kaddr + EXT2_DIR_REC_LEN(1));
	de->name_len = 2;
	de->rec_len = ext2_rec_len_to_disk(chunk_size - EXT2_DIR_REC_LEN(1));
	de->inode = cpu_to_le32(parent->i_ino);
	memcpy (de->name, "..\0", 4);
	ext2_set_de_type (de, inode);
	kunmap_atomic(kaddr, KM_USER0);
	err = ext2_commit_chunk(page, 0, chunk_size);
fail:
	page_cache_release(page);
	return err;
}