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
struct page {int dummy; } ;
struct nilfs_dir_entry {int name_len; int /*<<< orphan*/  name; void* inode; void* rec_len; } ;
struct inode {int /*<<< orphan*/  i_ino; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int NILFS_DIR_REC_LEN (int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int nilfs_chunk_size (struct inode*) ; 
 int nilfs_commit_chunk (struct page*,struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int nilfs_prepare_chunk (struct page*,struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nilfs_set_de_type (struct nilfs_dir_entry*,struct inode*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nilfs_make_empty(struct inode *inode, struct inode *parent)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page = grab_cache_page(mapping, 0);
	unsigned chunk_size = nilfs_chunk_size(inode);
	struct nilfs_dir_entry *de;
	int err;
	void *kaddr;

	if (!page)
		return -ENOMEM;

	err = nilfs_prepare_chunk(page, mapping, 0, chunk_size);
	if (unlikely(err)) {
		unlock_page(page);
		goto fail;
	}
	kaddr = kmap_atomic(page, KM_USER0);
	memset(kaddr, 0, chunk_size);
	de = (struct nilfs_dir_entry *)kaddr;
	de->name_len = 1;
	de->rec_len = cpu_to_le16(NILFS_DIR_REC_LEN(1));
	memcpy(de->name, ".\0\0", 4);
	de->inode = cpu_to_le64(inode->i_ino);
	nilfs_set_de_type(de, inode);

	de = (struct nilfs_dir_entry *)(kaddr + NILFS_DIR_REC_LEN(1));
	de->name_len = 2;
	de->rec_len = cpu_to_le16(chunk_size - NILFS_DIR_REC_LEN(1));
	de->inode = cpu_to_le64(parent->i_ino);
	memcpy(de->name, "..\0", 4);
	nilfs_set_de_type(de, inode);
	kunmap_atomic(kaddr, KM_USER0);
	err = nilfs_commit_chunk(page, mapping, 0, chunk_size);
fail:
	page_cache_release(page);
	return err;
}