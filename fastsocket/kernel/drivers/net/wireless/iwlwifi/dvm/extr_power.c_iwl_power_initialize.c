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
struct TYPE_4__ {int debug_sleep_level_override; int /*<<< orphan*/  sleep_cmd; int /*<<< orphan*/  bus_pm; } ;
struct iwl_priv {TYPE_2__ power_data; TYPE_1__* trans; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void iwl_power_initialize(struct iwl_priv *priv)
{
	priv->power_data.bus_pm = priv->trans->pm_support;

	priv->power_data.debug_sleep_level_override = -1;

	memset(&priv->power_data.sleep_cmd, 0,
		sizeof(priv->power_data.sleep_cmd));
}