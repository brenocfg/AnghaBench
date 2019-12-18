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
typedef  void page ;
struct nameidata {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd_set_link (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_getlink (struct dentry*,void**) ; 

void *page_follow_link_light(struct dentry *dentry, struct nameidata *nd)
{
	struct page *page = NULL;
	nd_set_link(nd, page_getlink(dentry, &page));
	return page;
}