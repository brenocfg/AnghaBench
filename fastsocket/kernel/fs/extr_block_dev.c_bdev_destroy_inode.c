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
struct bdev_inode {int dummy; } ;

/* Variables and functions */
 struct bdev_inode* BDEV_I (struct inode*) ; 
 int /*<<< orphan*/  bdev_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bdev_inode*) ; 

__attribute__((used)) static void bdev_destroy_inode(struct inode *inode)
{
	struct bdev_inode *bdi = BDEV_I(inode);

	kmem_cache_free(bdev_cachep, bdi);
}