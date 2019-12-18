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
struct TYPE_2__ {int /*<<< orphan*/  thermal_periodic; } ;
struct il_priv {TYPE_1__ _3945; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_bg_reg_txpower_periodic ; 

void
il3945_hw_setup_deferred_work(struct il_priv *il)
{
	INIT_DELAYED_WORK(&il->_3945.thermal_periodic,
			  il3945_bg_reg_txpower_periodic);
}