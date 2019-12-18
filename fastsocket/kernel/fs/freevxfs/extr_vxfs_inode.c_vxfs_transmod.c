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
struct vxfs_inode_info {int vii_mode; } ;
typedef  int mode_t ;

/* Variables and functions */
 int S_IFBLK ; 
 int S_IFCHR ; 
 int S_IFDIR ; 
 int S_IFIFO ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int S_IFSOCK ; 
 scalar_t__ VXFS_ISBLK (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISCHR (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISDIR (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISFIFO (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISLNK (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISREG (struct vxfs_inode_info*) ; 
 scalar_t__ VXFS_ISSOC (struct vxfs_inode_info*) ; 
 int VXFS_TYPE_MASK ; 

__attribute__((used)) static __inline__ mode_t
vxfs_transmod(struct vxfs_inode_info *vip)
{
	mode_t			ret = vip->vii_mode & ~VXFS_TYPE_MASK;

	if (VXFS_ISFIFO(vip))
		ret |= S_IFIFO;
	if (VXFS_ISCHR(vip))
		ret |= S_IFCHR;
	if (VXFS_ISDIR(vip))
		ret |= S_IFDIR;
	if (VXFS_ISBLK(vip))
		ret |= S_IFBLK;
	if (VXFS_ISLNK(vip))
		ret |= S_IFLNK;
	if (VXFS_ISREG(vip))
		ret |= S_IFREG;
	if (VXFS_ISSOC(vip))
		ret |= S_IFSOCK;

	return (ret);
}