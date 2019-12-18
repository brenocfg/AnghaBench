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
struct mmc_omap_slot {int /*<<< orphan*/  id; int /*<<< orphan*/  mmc; TYPE_1__* pdata; } ;
struct TYPE_2__ {int (* get_cover_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
int mmc_omap_cover_is_open(struct mmc_omap_slot *slot)
{
	if (slot->pdata->get_cover_state)
		return slot->pdata->get_cover_state(mmc_dev(slot->mmc),
						    slot->id);
	return 0;
}