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
struct v9fs_cookie {int /*<<< orphan*/  fscache; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int fscache_maybe_release_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 

int __v9fs_fscache_release_page(struct page *page, gfp_t gfp)
{
	struct inode *inode = page->mapping->host;
	struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);

	BUG_ON(!vcookie->fscache);

	return fscache_maybe_release_page(vcookie->fscache, page, gfp);
}