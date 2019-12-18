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
struct iwl_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  STATUS_SCAN_ABORTING ; 
 int /*<<< orphan*/  STATUS_SCAN_COMPLETE ; 
 int /*<<< orphan*/  STATUS_SCAN_HW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_complete_scan (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_force_scan_end(struct iwl_priv *priv)
{
	lockdep_assert_held(&priv->mutex);

	if (!test_bit(STATUS_SCANNING, &priv->status)) {
		IWL_DEBUG_SCAN(priv, "Forcing scan end while not scanning\n");
		return;
	}

	IWL_DEBUG_SCAN(priv, "Forcing scan end\n");
	clear_bit(STATUS_SCANNING, &priv->status);
	clear_bit(STATUS_SCAN_HW, &priv->status);
	clear_bit(STATUS_SCAN_ABORTING, &priv->status);
	clear_bit(STATUS_SCAN_COMPLETE, &priv->status);
	iwl_complete_scan(priv, true);
}