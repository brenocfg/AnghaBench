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
struct dst_node {int size; int /*<<< orphan*/  disk; } ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 struct block_device* bdget_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  i_size_write (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dst_node_set_size(struct dst_node *n)
{
	struct block_device *bdev;

	set_capacity(n->disk, n->size >> 9);

	bdev = bdget_disk(n->disk, 0);
	if (bdev) {
		mutex_lock(&bdev->bd_inode->i_mutex);
		i_size_write(bdev->bd_inode, n->size);
		mutex_unlock(&bdev->bd_inode->i_mutex);
		bdput(bdev);
	}
}