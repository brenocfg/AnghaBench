#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_atime; } ;
struct TYPE_5__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  cFYI (int,char*,int) ; 
 int cifs_read (struct file*,char*,int,int /*<<< orphan*/ *) ; 
 int cifs_readpage_from_fscache (TYPE_3__*,struct page*) ; 
 int /*<<< orphan*/  cifs_readpage_to_fscache (TYPE_3__*,struct page*) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

__attribute__((used)) static int cifs_readpage_worker(struct file *file, struct page *page,
	loff_t *poffset)
{
	char *read_data;
	int rc;

	/* Is the page cached? */
	rc = cifs_readpage_from_fscache(file->f_path.dentry->d_inode, page);
	if (rc == 0)
		goto read_complete;

	page_cache_get(page);
	read_data = kmap(page);
	/* for reads over a certain size could initiate async read ahead */

	rc = cifs_read(file, read_data, PAGE_CACHE_SIZE, poffset);

	if (rc < 0)
		goto io_error;
	else
		cFYI(1, "Bytes read %d", rc);

	file->f_path.dentry->d_inode->i_atime =
		current_fs_time(file->f_path.dentry->d_inode->i_sb);

	if (PAGE_CACHE_SIZE > rc)
		memset(read_data + rc, 0, PAGE_CACHE_SIZE - rc);

	flush_dcache_page(page);
	SetPageUptodate(page);

	/* send this page to the cache */
	cifs_readpage_to_fscache(file->f_path.dentry->d_inode, page);

	rc = 0;

io_error:
	kunmap(page);
	page_cache_release(page);

read_complete:
	return rc;
}