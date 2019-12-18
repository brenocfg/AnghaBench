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
struct inode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  JFFS2_XPREFIX_USER ; 
 int do_jffs2_getxattr (struct inode*,int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int jffs2_user_getxattr(struct inode *inode, const char *name,
			       void *buffer, size_t size)
{
	if (!strcmp(name, ""))
		return -EINVAL;
	return do_jffs2_getxattr(inode, JFFS2_XPREFIX_USER, name, buffer, size);
}