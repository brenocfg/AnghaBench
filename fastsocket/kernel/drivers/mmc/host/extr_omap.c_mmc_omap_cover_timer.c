#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmc_omap_slot {int /*<<< orphan*/  cover_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_omap_cover_timer(unsigned long arg)
{
	struct mmc_omap_slot *slot = (struct mmc_omap_slot *) arg;
	tasklet_schedule(&slot->cover_tasklet);
}