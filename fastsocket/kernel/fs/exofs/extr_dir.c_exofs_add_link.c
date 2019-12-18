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
struct page {int /*<<< orphan*/  mapping; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; TYPE_3__* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_numfiles; } ;
struct exofs_dir_entry {scalar_t__ rec_len; int name_len; scalar_t__ inode_no; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {unsigned char* name; int len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
typedef  int loff_t ;
struct TYPE_6__ {struct exofs_sb_info* s_fs_info; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 void* EXOFS_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,...) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 void* cpu_to_le16 (unsigned short) ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 unsigned long dir_pages (struct inode*) ; 
 unsigned int exofs_chunk_size (struct inode*) ; 
 int exofs_commit_chunk (struct page*,int,unsigned short) ; 
 struct page* exofs_get_page (struct inode*,unsigned long) ; 
 int exofs_last_byte (struct inode*,unsigned long) ; 
 scalar_t__ exofs_match (int,unsigned char const*,struct exofs_dir_entry*) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 int /*<<< orphan*/  exofs_set_de_type (struct exofs_dir_entry*,struct inode*) ; 
 int exofs_write_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned short,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 unsigned short le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 char* page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int exofs_add_link(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = dentry->d_parent->d_inode;
	const unsigned char *name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	unsigned chunk_size = exofs_chunk_size(dir);
	unsigned reclen = EXOFS_DIR_REC_LEN(namelen);
	unsigned short rec_len, name_len;
	struct page *page = NULL;
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;
	struct exofs_dir_entry *de;
	unsigned long npages = dir_pages(dir);
	unsigned long n;
	char *kaddr;
	loff_t pos;
	int err;

	for (n = 0; n <= npages; n++) {
		char *dir_end;

		page = exofs_get_page(dir, n);
		err = PTR_ERR(page);
		if (IS_ERR(page))
			goto out;
		lock_page(page);
		kaddr = page_address(page);
		dir_end = kaddr + exofs_last_byte(dir, n);
		de = (struct exofs_dir_entry *)kaddr;
		kaddr += PAGE_CACHE_SIZE - reclen;
		while ((char *)de <= kaddr) {
			if ((char *)de == dir_end) {
				name_len = 0;
				rec_len = chunk_size;
				de->rec_len = cpu_to_le16(chunk_size);
				de->inode_no = 0;
				goto got_it;
			}
			if (de->rec_len == 0) {
				EXOFS_ERR("ERROR: exofs_add_link: "
					"zero-length directory entry");
				err = -EIO;
				goto out_unlock;
			}
			err = -EEXIST;
			if (exofs_match(namelen, name, de))
				goto out_unlock;
			name_len = EXOFS_DIR_REC_LEN(de->name_len);
			rec_len = le16_to_cpu(de->rec_len);
			if (!de->inode_no && rec_len >= reclen)
				goto got_it;
			if (rec_len >= name_len + reclen)
				goto got_it;
			de = (struct exofs_dir_entry *) ((char *) de + rec_len);
		}
		unlock_page(page);
		exofs_put_page(page);
	}

	EXOFS_ERR("exofs_add_link: BAD dentry=%p or inode=%p", dentry, inode);
	return -EINVAL;

got_it:
	pos = page_offset(page) +
		(char *)de - (char *)page_address(page);
	err = exofs_write_begin(NULL, page->mapping, pos, rec_len, 0,
							&page, NULL);
	if (err)
		goto out_unlock;
	if (de->inode_no) {
		struct exofs_dir_entry *de1 =
			(struct exofs_dir_entry *)((char *)de + name_len);
		de1->rec_len = cpu_to_le16(rec_len - name_len);
		de->rec_len = cpu_to_le16(name_len);
		de = de1;
	}
	de->name_len = namelen;
	memcpy(de->name, name, namelen);
	de->inode_no = cpu_to_le64(inode->i_ino);
	exofs_set_de_type(de, inode);
	err = exofs_commit_chunk(page, pos, rec_len);
	dir->i_mtime = dir->i_ctime = CURRENT_TIME;
	mark_inode_dirty(dir);
	sbi->s_numfiles++;

out_put:
	exofs_put_page(page);
out:
	return err;
out_unlock:
	unlock_page(page);
	goto out_put;
}