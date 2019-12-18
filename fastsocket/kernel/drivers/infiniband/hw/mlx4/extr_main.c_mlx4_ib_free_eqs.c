#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num_comp_vectors; } ;
struct mlx4_ib_dev {scalar_t__* eq_table; int eq_added; TYPE_1__ ib_dev; } ;
struct TYPE_4__ {scalar_t__ num_comp_vectors; } ;
struct mlx4_dev {TYPE_2__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_release_eq (struct mlx4_dev*,scalar_t__) ; 

__attribute__((used)) static void mlx4_ib_free_eqs(struct mlx4_dev *dev, struct mlx4_ib_dev *ibdev)
{
	int i;

	/* no additional eqs were added */
	if (!ibdev->eq_table)
		return;

	/* Reset the advertised EQ number */
	ibdev->ib_dev.num_comp_vectors = dev->caps.num_comp_vectors;

	/* Free only the added eqs */
	for (i = 0; i < ibdev->eq_added; i++) {
		/* Don't free legacy eqs if used */
		if (ibdev->eq_table[i] <= dev->caps.num_comp_vectors)
			continue;
		mlx4_release_eq(dev, ibdev->eq_table[i]);
	}

	kfree(ibdev->eq_table);
}