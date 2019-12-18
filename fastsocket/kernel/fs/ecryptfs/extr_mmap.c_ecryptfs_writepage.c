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
struct writeback_control {int dummy; } ;
struct page {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int ecryptfs_encrypt_page (struct page*) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ecryptfs_writepage(struct page *page, struct writeback_control *wbc)
{
	int rc;

	rc = ecryptfs_encrypt_page(page);
	if (rc) {
		ecryptfs_printk(KERN_WARNING, "Error encrypting "
				"page (upper index [0x%.16x])\n", page->index);
		ClearPageUptodate(page);
		goto out;
	}
	SetPageUptodate(page);
	unlock_page(page);
out:
	return rc;
}