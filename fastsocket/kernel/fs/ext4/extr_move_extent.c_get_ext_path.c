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
struct ext4_ext_path {int /*<<< orphan*/ * p_ext; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_ext_find_extent (struct inode*,int /*<<< orphan*/ ,struct ext4_ext_path*) ; 
 size_t ext_depth (struct inode*) ; 

__attribute__((used)) static inline int
get_ext_path(struct inode *inode, ext4_lblk_t lblock,
		struct ext4_ext_path **path)
{
	int ret = 0;

	*path = ext4_ext_find_extent(inode, lblock, *path);
	if (IS_ERR(*path)) {
		ret = PTR_ERR(*path);
		*path = NULL;
	} else if ((*path)[ext_depth(inode)].p_ext == NULL)
		ret = -ENODATA;

	return ret;
}