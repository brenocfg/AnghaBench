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
struct page {scalar_t__ index; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  cFYI (int,char*,struct page*,int,int) ; 
 int cifs_readpage_worker (struct file*,struct page*,int*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int cifs_readpage(struct file *file, struct page *page)
{
	loff_t offset = (loff_t)page->index << PAGE_CACHE_SHIFT;
	int rc = -EACCES;
	int xid;

	xid = GetXid();

	if (file->private_data == NULL) {
		rc = -EBADF;
		FreeXid(xid);
		return rc;
	}

	cFYI(1, "readpage %p at offset %d 0x%x\n",
		 page, (int)offset, (int)offset);

	rc = cifs_readpage_worker(file, page, &offset);

	unlock_page(page);

	FreeXid(xid);
	return rc;
}