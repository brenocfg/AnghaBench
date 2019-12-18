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
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cb710_slot {TYPE_1__ pdev; } ;

/* Variables and functions */
 struct mmc_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct mmc_host *cb710_slot_to_mmc(struct cb710_slot *slot)
{
	return dev_get_drvdata(&slot->pdev.dev);
}