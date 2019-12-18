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
 int /*<<< orphan*/  JFFS2_INODE_INFO (struct inode*) ; 
 int /*<<< orphan*/  jffs2_inode_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jffs2_destroy_inode(struct inode *inode)
{
	kmem_cache_free(jffs2_inode_cachep, JFFS2_INODE_INFO(inode));
}