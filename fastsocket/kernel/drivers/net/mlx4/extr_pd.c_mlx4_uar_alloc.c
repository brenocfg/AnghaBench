#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_uar {int index; int pfn; int /*<<< orphan*/ * map; } ;
struct TYPE_4__ {int uar_page_size; } ;
struct mlx4_dev {int /*<<< orphan*/  pdev; TYPE_1__ caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  bitmap; } ;
struct TYPE_6__ {TYPE_2__ uar_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int mlx4_bitmap_alloc (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 TYPE_3__* mlx4_priv (struct mlx4_dev*) ; 
 scalar_t__ pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int) ; 

int mlx4_uar_alloc(struct mlx4_dev *dev, struct mlx4_uar *uar)
{
	int offset;

	uar->index = mlx4_bitmap_alloc(&mlx4_priv(dev)->uar_table.bitmap);
	if (uar->index == -1)
		return -ENOMEM;

	if (mlx4_is_slave(dev))
		offset = uar->index % ((int) pci_resource_len(dev->pdev, 2) /
				       dev->caps.uar_page_size);
	else
		offset = uar->index;
	uar->pfn = (pci_resource_start(dev->pdev, 2) >> PAGE_SHIFT) + offset;
	uar->map = NULL;
	return 0;
}