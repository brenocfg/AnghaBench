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
struct s3c_sdhci_platdata {scalar_t__ cfg_card; scalar_t__ cfg_gpio; int /*<<< orphan*/  max_width; } ;

/* Variables and functions */
 struct s3c_sdhci_platdata s3c_hsmmc0_def_platdata ; 

void s3c_sdhci0_set_platdata(struct s3c_sdhci_platdata *pd)
{
	struct s3c_sdhci_platdata *set = &s3c_hsmmc0_def_platdata;

	set->max_width = pd->max_width;

	if (pd->cfg_gpio)
		set->cfg_gpio = pd->cfg_gpio;
	if (pd->cfg_card)
		set->cfg_card = pd->cfg_card;
}