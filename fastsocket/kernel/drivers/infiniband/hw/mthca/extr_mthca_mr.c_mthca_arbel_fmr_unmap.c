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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ mpt; } ;
struct TYPE_4__ {TYPE_1__ arbel; } ;
struct mthca_fmr {TYPE_2__ mem; scalar_t__ maps; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_MPT_STATUS_SW ; 

void mthca_arbel_fmr_unmap(struct mthca_dev *dev, struct mthca_fmr *fmr)
{
	if (!fmr->maps)
		return;

	fmr->maps = 0;

	*(u8 *) fmr->mem.arbel.mpt = MTHCA_MPT_STATUS_SW;
}