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
 int /*<<< orphan*/  GFS2_EATYPE_USR ; 
 int gfs2_xattr_get (struct inode*,int /*<<< orphan*/ ,char const*,void*,size_t) ; 

__attribute__((used)) static int gfs2_xattr_user_get(struct inode *inode, const char *name,
			       void *buffer, size_t size)
{
	return gfs2_xattr_get(inode, GFS2_EATYPE_USR, name, buffer, size);
}