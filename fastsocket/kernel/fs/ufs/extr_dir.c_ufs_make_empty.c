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
struct ufs_dir_entry {int /*<<< orphan*/  d_name; void* d_reclen; void* d_ino; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; struct address_space* i_mapping; struct super_block* i_sb; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {TYPE_1__* s_uspi; } ;
struct TYPE_3__ {unsigned int s_dirblksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 scalar_t__ UFS_DIR_REC_LEN (int) ; 
 TYPE_2__* UFS_SB (struct super_block*) ; 
 int __ufs_write_begin (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 void* cpu_to_fs16 (struct super_block*,scalar_t__) ; 
 void* cpu_to_fs32 (struct super_block*,int /*<<< orphan*/ ) ; 
 int fs16_to_cpu (struct super_block*,void*) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int ufs_commit_chunk (struct page*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  ufs_set_de_namlen (struct super_block*,struct ufs_dir_entry*,int) ; 
 int /*<<< orphan*/  ufs_set_de_type (struct super_block*,struct ufs_dir_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int ufs_make_empty(struct inode * inode, struct inode *dir)
{
	struct super_block * sb = dir->i_sb;
	struct address_space *mapping = inode->i_mapping;
	struct page *page = grab_cache_page(mapping, 0);
	const unsigned int chunk_size = UFS_SB(sb)->s_uspi->s_dirblksize;
	struct ufs_dir_entry * de;
	char *base;
	int err;

	if (!page)
		return -ENOMEM;

	err = __ufs_write_begin(NULL, mapping, 0, chunk_size,
				AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err) {
		unlock_page(page);
		goto fail;
	}

	kmap(page);
	base = (char*)page_address(page);
	memset(base, 0, PAGE_CACHE_SIZE);

	de = (struct ufs_dir_entry *) base;

	de->d_ino = cpu_to_fs32(sb, inode->i_ino);
	ufs_set_de_type(sb, de, inode->i_mode);
	ufs_set_de_namlen(sb, de, 1);
	de->d_reclen = cpu_to_fs16(sb, UFS_DIR_REC_LEN(1));
	strcpy (de->d_name, ".");
	de = (struct ufs_dir_entry *)
		((char *)de + fs16_to_cpu(sb, de->d_reclen));
	de->d_ino = cpu_to_fs32(sb, dir->i_ino);
	ufs_set_de_type(sb, de, dir->i_mode);
	de->d_reclen = cpu_to_fs16(sb, chunk_size - UFS_DIR_REC_LEN(1));
	ufs_set_de_namlen(sb, de, 2);
	strcpy (de->d_name, "..");
	kunmap(page);

	err = ufs_commit_chunk(page, 0, chunk_size);
fail:
	page_cache_release(page);
	return err;
}