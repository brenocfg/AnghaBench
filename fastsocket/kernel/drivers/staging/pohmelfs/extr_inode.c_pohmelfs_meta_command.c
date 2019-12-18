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
typedef  int /*<<< orphan*/  u64 ;
struct pohmelfs_inode {int /*<<< orphan*/  ino; } ;
typedef  int /*<<< orphan*/  netfs_trans_complete_t ;

/* Variables and functions */
 int pohmelfs_meta_command_data (struct pohmelfs_inode*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int pohmelfs_meta_command(struct pohmelfs_inode *pi, unsigned int cmd_op, unsigned int flags,
		netfs_trans_complete_t complete, void *priv, u64 start)
{
	return pohmelfs_meta_command_data(pi, pi->ino, cmd_op, NULL, flags, complete, priv, start);
}