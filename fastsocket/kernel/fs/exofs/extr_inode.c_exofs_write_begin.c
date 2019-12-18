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
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*) ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int _readpage (struct page*,int) ; 
 int simple_write_begin (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page**,void**) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int exofs_write_begin(struct file *file, struct address_space *mapping,
		loff_t pos, unsigned len, unsigned flags,
		struct page **pagep, void **fsdata)
{
	int ret = 0;
	struct page *page;

	page = *pagep;
	if (page == NULL) {
		ret = simple_write_begin(file, mapping, pos, len, flags, pagep,
					 fsdata);
		if (ret) {
			EXOFS_DBGMSG("simple_write_begin faild\n");
			return ret;
		}

		page = *pagep;
	}

	 /* read modify write */
	if (!PageUptodate(page) && (len != PAGE_CACHE_SIZE)) {
		ret = _readpage(page, true);
		if (ret) {
			/*SetPageError was done by _readpage. Is it ok?*/
			unlock_page(page);
			EXOFS_DBGMSG("__readpage_filler faild\n");
		}
	}

	return ret;
}