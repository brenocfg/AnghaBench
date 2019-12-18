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
struct mlx4_ib_dev {TYPE_1__* dev; } ;
struct TYPE_2__ {int num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_is_master (TYPE_1__*) ; 
 int /*<<< orphan*/  register_one_pkey_tree (struct mlx4_ib_dev*,int) ; 

__attribute__((used)) static int register_pkey_tree(struct mlx4_ib_dev *device)
{
	int i;

	if (!mlx4_is_master(device->dev))
		return 0;

	for (i = 0; i <= device->dev->num_vfs; ++i)
		register_one_pkey_tree(device, i);

	return 0;
}