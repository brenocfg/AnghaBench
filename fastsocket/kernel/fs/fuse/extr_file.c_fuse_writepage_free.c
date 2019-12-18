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
struct fuse_req {int /*<<< orphan*/  ff; int /*<<< orphan*/ * pages; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_file_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_writepage_free(struct fuse_conn *fc, struct fuse_req *req)
{
	__free_page(req->pages[0]);
	fuse_file_put(req->ff);
}