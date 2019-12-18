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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct cifs_writedata {int nr_pages; int /*<<< orphan*/ * pages; TYPE_2__* cfile; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SetPageError (int /*<<< orphan*/ ) ; 
 int cifs_async_writev (struct cifs_writedata*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_writev_requeue(struct cifs_writedata *wdata)
{
	int i, rc;
	struct inode *inode = wdata->cfile->dentry->d_inode;

	for (i = 0; i < wdata->nr_pages; i++) {
		lock_page(wdata->pages[i]);
		clear_page_dirty_for_io(wdata->pages[i]);
	}

	do {
		rc = cifs_async_writev(wdata);
	} while (rc == -EAGAIN);

	for (i = 0; i < wdata->nr_pages; i++) {
		unlock_page(wdata->pages[i]);
		if (rc != 0) {
			SetPageError(wdata->pages[i]);
			end_page_writeback(wdata->pages[i]);
			page_cache_release(wdata->pages[i]);
		}
	}

	mapping_set_error(inode->i_mapping, rc);
}