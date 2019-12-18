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
struct nfs_page {TYPE_2__* wb_page; } ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (TYPE_2__*) ; 

__attribute__((used)) static void
nfs_mark_request_dirty(struct nfs_page *req)
{
	__set_page_dirty_nobuffers(req->wb_page);
	__mark_inode_dirty(req->wb_page->mapping->host, I_DIRTY_DATASYNC);
}