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
struct iwl_priv {scalar_t__ scan_type; TYPE_2__* scan_request; int /*<<< orphan*/  scan_vif; int /*<<< orphan*/  status; int /*<<< orphan*/  scan_check; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__** channels; } ;
struct TYPE_3__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*,...) ; 
 scalar_t__ IWL_SCAN_NORMAL ; 
 scalar_t__ IWL_SCAN_ROC ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  STATUS_SCAN_ABORTING ; 
 int /*<<< orphan*/  STATUS_SCAN_COMPLETE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_complete_scan (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_is_ready_rf (struct iwl_priv*) ; 
 int iwl_scan_initiate (struct iwl_priv*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_scan_roc_expired (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_post_scan (struct iwl_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_process_scan_complete(struct iwl_priv *priv)
{
	bool aborted;

	lockdep_assert_held(&priv->mutex);

	if (!test_and_clear_bit(STATUS_SCAN_COMPLETE, &priv->status))
		return;

	IWL_DEBUG_SCAN(priv, "Completed scan.\n");

	cancel_delayed_work(&priv->scan_check);

	aborted = test_and_clear_bit(STATUS_SCAN_ABORTING, &priv->status);
	if (aborted)
		IWL_DEBUG_SCAN(priv, "Aborted scan completed.\n");

	if (!test_and_clear_bit(STATUS_SCANNING, &priv->status)) {
		IWL_DEBUG_SCAN(priv, "Scan already completed.\n");
		goto out_settings;
	}

	if (priv->scan_type == IWL_SCAN_ROC)
		iwl_scan_roc_expired(priv);

	if (priv->scan_type != IWL_SCAN_NORMAL && !aborted) {
		int err;

		/* Check if mac80211 requested scan during our internal scan */
		if (priv->scan_request == NULL)
			goto out_complete;

		/* If so request a new scan */
		err = iwl_scan_initiate(priv, priv->scan_vif, IWL_SCAN_NORMAL,
					priv->scan_request->channels[0]->band);
		if (err) {
			IWL_DEBUG_SCAN(priv,
				"failed to initiate pending scan: %d\n", err);
			aborted = true;
			goto out_complete;
		}

		return;
	}

out_complete:
	iwl_complete_scan(priv, aborted);

out_settings:
	/* Can we still talk to firmware ? */
	if (!iwl_is_ready_rf(priv))
		return;

	iwlagn_post_scan(priv);
}