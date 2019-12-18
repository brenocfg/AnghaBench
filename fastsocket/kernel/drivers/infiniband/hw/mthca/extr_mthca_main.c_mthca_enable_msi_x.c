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
struct TYPE_4__ {TYPE_1__* eq; } ;
struct mthca_dev {TYPE_2__ eq_table; int /*<<< orphan*/  pdev; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  msi_x_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct msix_entry*) ; 
 size_t MTHCA_EQ_ASYNC ; 
 size_t MTHCA_EQ_CMD ; 
 size_t MTHCA_EQ_COMP ; 
 int /*<<< orphan*/  mthca_info (struct mthca_dev*,char*,int) ; 
 int pci_enable_msix (int /*<<< orphan*/ ,struct msix_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_enable_msi_x(struct mthca_dev *mdev)
{
	struct msix_entry entries[3];
	int err;

	entries[0].entry = 0;
	entries[1].entry = 1;
	entries[2].entry = 2;

	err = pci_enable_msix(mdev->pdev, entries, ARRAY_SIZE(entries));
	if (err) {
		if (err > 0)
			mthca_info(mdev, "Only %d MSI-X vectors available, "
				   "not using MSI-X\n", err);
		return err;
	}

	mdev->eq_table.eq[MTHCA_EQ_COMP ].msi_x_vector = entries[0].vector;
	mdev->eq_table.eq[MTHCA_EQ_ASYNC].msi_x_vector = entries[1].vector;
	mdev->eq_table.eq[MTHCA_EQ_CMD  ].msi_x_vector = entries[2].vector;

	return 0;
}