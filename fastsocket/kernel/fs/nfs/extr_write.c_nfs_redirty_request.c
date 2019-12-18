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
struct nfs_page {int /*<<< orphan*/  wb_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_end_page_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_mark_request_dirty (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_request (struct nfs_page*) ; 

__attribute__((used)) static void nfs_redirty_request(struct nfs_page *req)
{
	nfs_mark_request_dirty(req);
	nfs_unlock_request(req);
	nfs_end_page_writeback(req->wb_page);
	nfs_release_request(req);
}