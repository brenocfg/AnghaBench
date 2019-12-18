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
struct dst_node {int dummy; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct dst_node* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_node_get (struct dst_node*) ; 

__attribute__((used)) static int dst_bdev_open(struct block_device *bdev, fmode_t mode)
{
	struct dst_node *n = bdev->bd_disk->private_data;

	dst_node_get(n);
	return 0;
}