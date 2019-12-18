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
struct nameidata {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int configfs_getlink (struct dentry*,char*) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 

__attribute__((used)) static void *configfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	int error = -ENOMEM;
	unsigned long page = get_zeroed_page(GFP_KERNEL);

	if (page) {
		error = configfs_getlink(dentry, (char *)page);
		if (!error) {
			nd_set_link(nd, (char *)page);
			return (void *)page;
		}
	}

	nd_set_link(nd, ERR_PTR(error));
	return NULL;
}