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
struct nilfs_bmap {int /*<<< orphan*/  b_inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_I_NILFS (int /*<<< orphan*/ ) ; 
 struct inode* nilfs_dat_inode (int /*<<< orphan*/ ) ; 

struct inode *nilfs_bmap_get_dat(const struct nilfs_bmap *bmap)
{
	return nilfs_dat_inode(NILFS_I_NILFS(bmap->b_inode));
}