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
struct page {scalar_t__ index; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 TYPE_1__* FILE_HOSTFS_I (struct file*) ; 
 long long PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int read_file (int /*<<< orphan*/ ,long long*,char*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int hostfs_readpage(struct file *file, struct page *page)
{
	char *buffer;
	long long start;
	int err = 0;

	start = (long long) page->index << PAGE_CACHE_SHIFT;
	buffer = kmap(page);
	err = read_file(FILE_HOSTFS_I(file)->fd, &start, buffer,
			PAGE_CACHE_SIZE);
	if (err < 0)
		goto out;

	memset(&buffer[err], 0, PAGE_CACHE_SIZE - err);

	flush_dcache_page(page);
	SetPageUptodate(page);
	if (PageError(page)) ClearPageError(page);
	err = 0;
 out:
	kunmap(page);
	unlock_page(page);
	return err;
}