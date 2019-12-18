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
struct inode {int dummy; } ;

/* Variables and functions */
 int jffs2_do_readpage_nolock (struct inode*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int jffs2_do_readpage_unlock(struct inode *inode, struct page *pg)
{
	int ret = jffs2_do_readpage_nolock(inode, pg);
	unlock_page(pg);
	return ret;
}