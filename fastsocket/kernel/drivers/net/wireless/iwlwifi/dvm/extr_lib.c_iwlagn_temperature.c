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
struct TYPE_3__ {int /*<<< orphan*/  temperature; } ;
struct TYPE_4__ {TYPE_1__ common; int /*<<< orphan*/  lock; } ;
struct iwl_priv {TYPE_2__ statistics; int /*<<< orphan*/  temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_tt_handler (struct iwl_priv*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwlagn_temperature(struct iwl_priv *priv)
{
	lockdep_assert_held(&priv->statistics.lock);

	/* store temperature from correct statistics (in Celsius) */
	priv->temperature = le32_to_cpu(priv->statistics.common.temperature);
	iwl_tt_handler(priv);
}