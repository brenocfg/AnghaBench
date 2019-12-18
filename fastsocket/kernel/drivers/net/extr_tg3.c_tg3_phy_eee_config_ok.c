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
struct TYPE_2__ {scalar_t__ advertised; scalar_t__ tx_lpi_timer; scalar_t__ tx_lpi_enabled; scalar_t__ eee_enabled; } ;
struct tg3 {int phy_flags; TYPE_1__ eee; } ;
struct ethtool_eee {scalar_t__ advertised; scalar_t__ tx_lpi_timer; scalar_t__ tx_lpi_enabled; } ;

/* Variables and functions */
 int TG3_PHYFLG_EEE_CAP ; 
 int /*<<< orphan*/  tg3_eee_pull_config (struct tg3*,struct ethtool_eee*) ; 

__attribute__((used)) static bool tg3_phy_eee_config_ok(struct tg3 *tp)
{
	struct ethtool_eee eee;

	if (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		return true;

	tg3_eee_pull_config(tp, &eee);

	if (tp->eee.eee_enabled) {
		if (tp->eee.advertised != eee.advertised ||
		    tp->eee.tx_lpi_timer != eee.tx_lpi_timer ||
		    tp->eee.tx_lpi_enabled != eee.tx_lpi_enabled)
			return false;
	} else {
		/* EEE is disabled but we're advertising */
		if (eee.advertised)
			return false;
	}

	return true;
}