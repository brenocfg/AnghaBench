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
struct pohmelfs_name {int dummy; } ;
struct pohmelfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pohmelfs_fix_offset (struct pohmelfs_inode*,struct pohmelfs_name*) ; 
 int /*<<< orphan*/  pohmelfs_name_free (struct pohmelfs_inode*,struct pohmelfs_name*) ; 

void pohmelfs_name_del(struct pohmelfs_inode *parent, struct pohmelfs_name *node)
{
	pohmelfs_fix_offset(parent, node);
	pohmelfs_name_free(parent, node);
}