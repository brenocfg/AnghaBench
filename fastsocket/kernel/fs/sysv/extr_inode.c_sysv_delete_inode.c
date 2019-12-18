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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysv_free_inode (struct inode*) ; 
 int /*<<< orphan*/  sysv_truncate (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysv_delete_inode(struct inode *inode)
{
	truncate_inode_pages(&inode->i_data, 0);
	inode->i_size = 0;
	sysv_truncate(inode);
	sysv_free_inode(inode);
}