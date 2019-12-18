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
struct v9fs_cookie {int /*<<< orphan*/  fscache; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,...) ; 
 int fscache_write_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 
 int /*<<< orphan*/  v9fs_uncache_page (struct inode*,struct page*) ; 

void __v9fs_readpage_to_fscache(struct inode *inode, struct page *page)
{
	int ret;
	const struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);

	P9_DPRINTK(P9_DEBUG_FSC, "inode %p page %p", inode, page);
	ret = fscache_write_page(vcookie->fscache, page, GFP_KERNEL);
	P9_DPRINTK(P9_DEBUG_FSC, "ret =  %d", ret);
	if (ret != 0)
		v9fs_uncache_page(inode, page);
}