#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext3_journalled_aops ; 
 int /*<<< orphan*/  ext3_ordered_aops ; 
 scalar_t__ ext3_should_order_data (struct inode*) ; 
 scalar_t__ ext3_should_writeback_data (struct inode*) ; 
 int /*<<< orphan*/  ext3_writeback_aops ; 

void ext3_set_aops(struct inode *inode)
{
	if (ext3_should_order_data(inode))
		inode->i_mapping->a_ops = &ext3_ordered_aops;
	else if (ext3_should_writeback_data(inode))
		inode->i_mapping->a_ops = &ext3_writeback_aops;
	else
		inode->i_mapping->a_ops = &ext3_journalled_aops;
}