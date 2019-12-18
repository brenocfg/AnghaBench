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
struct fsl_msi {int /*<<< orphan*/  bitmap; TYPE_1__* irqhost; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_MSI_IRQS ; 
 int msi_bitmap_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_bitmap_free (int /*<<< orphan*/ *) ; 
 int msi_bitmap_reserve_dt_hwirqs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_msi_init_allocator(struct fsl_msi *msi_data)
{
	int rc;

	rc = msi_bitmap_alloc(&msi_data->bitmap, NR_MSI_IRQS,
			      msi_data->irqhost->of_node);
	if (rc)
		return rc;

	rc = msi_bitmap_reserve_dt_hwirqs(&msi_data->bitmap);
	if (rc < 0) {
		msi_bitmap_free(&msi_data->bitmap);
		return rc;
	}

	return 0;
}