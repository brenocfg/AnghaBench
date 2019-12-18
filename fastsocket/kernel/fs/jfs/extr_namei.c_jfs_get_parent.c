#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_4__* d_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  idotdot; } ;
struct TYPE_6__ {TYPE_1__ header; } ;
struct TYPE_7__ {TYPE_2__ i_dtroot; } ;

/* Variables and functions */
 TYPE_3__* JFS_IP (TYPE_4__*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

struct dentry *jfs_get_parent(struct dentry *dentry)
{
	unsigned long parent_ino;

	parent_ino =
		le32_to_cpu(JFS_IP(dentry->d_inode)->i_dtroot.header.idotdot);

	return d_obtain_alias(jfs_iget(dentry->d_inode->i_sb, parent_ino));
}