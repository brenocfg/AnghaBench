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
struct TYPE_4__ {int /*<<< orphan*/  reserved_pds; int /*<<< orphan*/  num_pds; } ;
struct TYPE_3__ {int /*<<< orphan*/  alloc; } ;
struct mthca_dev {TYPE_2__ limits; TYPE_1__ pd_table; } ;

/* Variables and functions */
 int mthca_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mthca_init_pd_table(struct mthca_dev *dev)
{
	return mthca_alloc_init(&dev->pd_table.alloc,
				dev->limits.num_pds,
				(1 << 24) - 1,
				dev->limits.reserved_pds);
}