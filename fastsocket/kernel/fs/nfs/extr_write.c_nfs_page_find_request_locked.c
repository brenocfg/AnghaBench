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
struct nfs_page {int /*<<< orphan*/  wb_kref; } ;

/* Variables and functions */
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ page_private (struct page*) ; 

__attribute__((used)) static struct nfs_page *nfs_page_find_request_locked(struct page *page)
{
	struct nfs_page *req = NULL;

	if (PagePrivate(page)) {
		req = (struct nfs_page *)page_private(page);
		if (req != NULL)
			kref_get(&req->wb_kref);
	}
	return req;
}