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
struct nameidata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PATH_MAX ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 size_t min (int,scalar_t__) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 
 int v9fs_readlink (struct dentry*,char*,scalar_t__) ; 

__attribute__((used)) static void *v9fs_vfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	int len = 0;
	char *link = __getname();

	P9_DPRINTK(P9_DEBUG_VFS, "%s n", dentry->d_name.name);

	if (!link)
		link = ERR_PTR(-ENOMEM);
	else {
		len = v9fs_readlink(dentry, link, PATH_MAX);

		if (len < 0) {
			__putname(link);
			link = ERR_PTR(len);
		} else
			link[min(len, PATH_MAX-1)] = 0;
	}
	nd_set_link(nd, link);

	return NULL;
}