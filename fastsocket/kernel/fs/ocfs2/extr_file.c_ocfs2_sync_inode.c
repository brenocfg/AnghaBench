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
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_sync_inode(struct inode *inode)
{
	filemap_fdatawrite(inode->i_mapping);
	return sync_mapping_buffers(inode->i_mapping);
}