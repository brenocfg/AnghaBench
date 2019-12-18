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
struct inode {scalar_t__ i_ino; } ;
struct exofs_dir_entry {scalar_t__ rec_len; scalar_t__ inode_no; char* name; int name_len; } ;

/* Variables and functions */
 scalar_t__ EXOFS_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,char*,struct exofs_dir_entry*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned long dir_pages (struct inode*) ; 
 struct page* exofs_get_page (struct inode*,unsigned long) ; 
 scalar_t__ exofs_last_byte (struct inode*,unsigned long) ; 
 struct exofs_dir_entry* exofs_next_entry (struct exofs_dir_entry*) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 char* page_address (struct page*) ; 

int exofs_empty_dir(struct inode *inode)
{
	struct page *page = NULL;
	unsigned long i, npages = dir_pages(inode);

	for (i = 0; i < npages; i++) {
		char *kaddr;
		struct exofs_dir_entry *de;
		page = exofs_get_page(inode, i);

		if (IS_ERR(page))
			continue;

		kaddr = page_address(page);
		de = (struct exofs_dir_entry *)kaddr;
		kaddr += exofs_last_byte(inode, i) - EXOFS_DIR_REC_LEN(1);

		while ((char *)de <= kaddr) {
			if (de->rec_len == 0) {
				EXOFS_ERR("ERROR: exofs_empty_dir: "
					  "zero-length directory entry"
					  "kaddr=%p, de=%p\n", kaddr, de);
				goto not_empty;
			}
			if (de->inode_no != 0) {
				/* check for . and .. */
				if (de->name[0] != '.')
					goto not_empty;
				if (de->name_len > 2)
					goto not_empty;
				if (de->name_len < 2) {
					if (le64_to_cpu(de->inode_no) !=
					    inode->i_ino)
						goto not_empty;
				} else if (de->name[1] != '.')
					goto not_empty;
			}
			de = exofs_next_entry(de);
		}
		exofs_put_page(page);
	}
	return 1;

not_empty:
	exofs_put_page(page);
	return 0;
}