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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_inode {struct inode i_inode; int /*<<< orphan*/ * i_res; int /*<<< orphan*/ * i_rgd; int /*<<< orphan*/ * i_gl; scalar_t__ i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gfs2_inode_cachep ; 
 struct gfs2_inode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *gfs2_alloc_inode(struct super_block *sb)
{
	struct gfs2_inode *ip;

	ip = kmem_cache_alloc(gfs2_inode_cachep, GFP_KERNEL);
	if (ip) {
		ip->i_flags = 0;
		ip->i_gl = NULL;
		ip->i_rgd = NULL;
		ip->i_res = NULL;
	}
	return &ip->i_inode;
}