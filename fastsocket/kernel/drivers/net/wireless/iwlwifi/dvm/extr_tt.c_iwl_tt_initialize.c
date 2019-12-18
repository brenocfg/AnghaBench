#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_tt_trans {int dummy; } ;
struct iwl_tt_restriction {int dummy; } ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct iwl_tt_mgmt {int state; int advanced_tt; struct iwl_tt_trans* restriction; struct iwl_tt_trans* transaction; TYPE_3__ ct_kill_waiting_tm; TYPE_3__ ct_kill_exit_tm; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; TYPE_2__* cfg; int /*<<< orphan*/  ct_exit; int /*<<< orphan*/  ct_enter; int /*<<< orphan*/  tt_work; } ;
struct TYPE_5__ {TYPE_1__* base_params; } ;
struct TYPE_4__ {scalar_t__ adv_thermal_throttle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int IWL_TI_0 ; 
 int IWL_TI_1 ; 
 int IWL_TI_2 ; 
 int IWL_TI_CT_KILL ; 
 int IWL_TI_STATE_MAX ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  iwl_bg_ct_enter ; 
 int /*<<< orphan*/  iwl_bg_ct_exit ; 
 int /*<<< orphan*/  iwl_bg_tt_work ; 
 int /*<<< orphan*/  iwl_tt_check_exit_ct_kill ; 
 int /*<<< orphan*/  iwl_tt_ready_for_ct_kill ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iwl_tt_trans*) ; 
 int /*<<< orphan*/  memcpy (struct iwl_tt_trans*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iwl_tt_mgmt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * restriction_range ; 
 int /*<<< orphan*/ * tt_range_0 ; 
 int /*<<< orphan*/ * tt_range_1 ; 
 int /*<<< orphan*/ * tt_range_2 ; 
 int /*<<< orphan*/ * tt_range_3 ; 

void iwl_tt_initialize(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;
	int size = sizeof(struct iwl_tt_trans) * (IWL_TI_STATE_MAX - 1);
	struct iwl_tt_trans *transaction;

	IWL_DEBUG_TEMP(priv, "Initialize Thermal Throttling\n");

	memset(tt, 0, sizeof(struct iwl_tt_mgmt));

	tt->state = IWL_TI_0;
	init_timer(&priv->thermal_throttle.ct_kill_exit_tm);
	priv->thermal_throttle.ct_kill_exit_tm.data = (unsigned long)priv;
	priv->thermal_throttle.ct_kill_exit_tm.function =
		iwl_tt_check_exit_ct_kill;
	init_timer(&priv->thermal_throttle.ct_kill_waiting_tm);
	priv->thermal_throttle.ct_kill_waiting_tm.data =
		(unsigned long)priv;
	priv->thermal_throttle.ct_kill_waiting_tm.function =
		iwl_tt_ready_for_ct_kill;
	/* setup deferred ct kill work */
	INIT_WORK(&priv->tt_work, iwl_bg_tt_work);
	INIT_WORK(&priv->ct_enter, iwl_bg_ct_enter);
	INIT_WORK(&priv->ct_exit, iwl_bg_ct_exit);

	if (priv->cfg->base_params->adv_thermal_throttle) {
		IWL_DEBUG_TEMP(priv, "Advanced Thermal Throttling\n");
		tt->restriction = kcalloc(IWL_TI_STATE_MAX,
					  sizeof(struct iwl_tt_restriction),
					  GFP_KERNEL);
		tt->transaction = kcalloc(IWL_TI_STATE_MAX *
					  (IWL_TI_STATE_MAX - 1),
					  sizeof(struct iwl_tt_trans),
					  GFP_KERNEL);
		if (!tt->restriction || !tt->transaction) {
			IWL_ERR(priv, "Fallback to Legacy Throttling\n");
			priv->thermal_throttle.advanced_tt = false;
			kfree(tt->restriction);
			tt->restriction = NULL;
			kfree(tt->transaction);
			tt->transaction = NULL;
		} else {
			transaction = tt->transaction +
				(IWL_TI_0 * (IWL_TI_STATE_MAX - 1));
			memcpy(transaction, &tt_range_0[0], size);
			transaction = tt->transaction +
				(IWL_TI_1 * (IWL_TI_STATE_MAX - 1));
			memcpy(transaction, &tt_range_1[0], size);
			transaction = tt->transaction +
				(IWL_TI_2 * (IWL_TI_STATE_MAX - 1));
			memcpy(transaction, &tt_range_2[0], size);
			transaction = tt->transaction +
				(IWL_TI_CT_KILL * (IWL_TI_STATE_MAX - 1));
			memcpy(transaction, &tt_range_3[0], size);
			size = sizeof(struct iwl_tt_restriction) *
				IWL_TI_STATE_MAX;
			memcpy(tt->restriction,
				&restriction_range[0], size);
			priv->thermal_throttle.advanced_tt = true;
		}
	} else {
		IWL_DEBUG_TEMP(priv, "Legacy Thermal Throttling\n");
		priv->thermal_throttle.advanced_tt = false;
	}
}