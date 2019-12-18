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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct exofs_i_info {unsigned long i_dir_start_lookup; } ;
struct exofs_dir_entry {scalar_t__ rec_len; } ;
struct TYPE_2__ {unsigned char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 unsigned int EXOFS_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 unsigned long dir_pages (struct inode*) ; 
 struct page* exofs_get_page (struct inode*,unsigned long) ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 unsigned int exofs_last_byte (struct inode*,unsigned long) ; 
 scalar_t__ exofs_match (int,unsigned char const*,struct exofs_dir_entry*) ; 
 struct exofs_dir_entry* exofs_next_entry (struct exofs_dir_entry*) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 char* page_address (struct page*) ; 

struct exofs_dir_entry *exofs_find_entry(struct inode *dir,
			struct dentry *dentry, struct page **res_page)
{
	const unsigned char *name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	unsigned reclen = EXOFS_DIR_REC_LEN(namelen);
	unsigned long start, n;
	unsigned long npages = dir_pages(dir);
	struct page *page = NULL;
	struct exofs_i_info *oi = exofs_i(dir);
	struct exofs_dir_entry *de;

	if (npages == 0)
		goto out;

	*res_page = NULL;

	start = oi->i_dir_start_lookup;
	if (start >= npages)
		start = 0;
	n = start;
	do {
		char *kaddr;
		page = exofs_get_page(dir, n);
		if (!IS_ERR(page)) {
			kaddr = page_address(page);
			de = (struct exofs_dir_entry *) kaddr;
			kaddr += exofs_last_byte(dir, n) - reclen;
			while ((char *) de <= kaddr) {
				if (de->rec_len == 0) {
					EXOFS_ERR(
						"ERROR: exofs_find_entry: "
						"zero-length directory entry");
					exofs_put_page(page);
					goto out;
				}
				if (exofs_match(namelen, name, de))
					goto found;
				de = exofs_next_entry(de);
			}
			exofs_put_page(page);
		}
		if (++n >= npages)
			n = 0;
	} while (n != start);
out:
	return NULL;

found:
	*res_page = page;
	oi->i_dir_start_lookup = n;
	return de;
}