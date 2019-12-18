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
struct writeback_control {int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int sync_inode (struct inode*,struct writeback_control*) ; 

int nfs_wb_all(struct inode *inode)
{
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = LONG_MAX,
		.range_start = 0,
		.range_end = LLONG_MAX,
	};

	return sync_inode(inode, &wbc);
}