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
struct pohmelfs_name {scalar_t__ len; } ;
struct pohmelfs_inode {int /*<<< orphan*/  total_len; } ;

/* Variables and functions */

__attribute__((used)) static void pohmelfs_fix_offset(struct pohmelfs_inode *parent, struct pohmelfs_name *node)
{
	parent->total_len -= node->len;
}