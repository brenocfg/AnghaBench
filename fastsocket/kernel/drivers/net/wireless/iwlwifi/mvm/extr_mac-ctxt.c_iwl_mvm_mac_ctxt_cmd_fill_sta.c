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
typedef  int u32 ;
struct iwl_mvm {TYPE_2__* hw; } ;
struct iwl_mac_data_sta {void* assoc_id; void* listen_interval; void* dtim_reciprocal; void* dtim_interval; void* bi_reciprocal; void* bi; void* is_assoc; void* dtim_time; int /*<<< orphan*/  dtim_tsf; } ;
struct TYPE_6__ {int dtim_period; int sync_dtim_count; int beacon_int; int sync_device_ts; int aid; scalar_t__ sync_tsf; scalar_t__ assoc; } ;
struct ieee80211_vif {TYPE_3__ bss_conf; } ;
struct TYPE_4__ {int listen_interval; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int iwl_mvm_reciprocal (int) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_mac_ctxt_cmd_fill_sta(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif,
					  struct iwl_mac_data_sta *ctxt_sta,
					  bool force_assoc_off)
{
	/* We need the dtim_period to set the MAC as associated */
	if (vif->bss_conf.assoc && vif->bss_conf.dtim_period &&
	    !force_assoc_off) {
		u32 dtim_offs;

		/*
		 * The DTIM count counts down, so when it is N that means N
		 * more beacon intervals happen until the DTIM TBTT. Therefore
		 * add this to the current time. If that ends up being in the
		 * future, the firmware will handle it.
		 *
		 * Also note that the system_timestamp (which we get here as
		 * "sync_device_ts") and TSF timestamp aren't at exactly the
		 * same offset in the frame -- the TSF is at the first symbol
		 * of the TSF, the system timestamp is at signal acquisition
		 * time. This means there's an offset between them of at most
		 * a few hundred microseconds (24 * 8 bits + PLCP time gives
		 * 384us in the longest case), this is currently not relevant
		 * as the firmware wakes up around 2ms before the TBTT.
		 */
		dtim_offs = vif->bss_conf.sync_dtim_count *
				vif->bss_conf.beacon_int;
		/* convert TU to usecs */
		dtim_offs *= 1024;

		ctxt_sta->dtim_tsf =
			cpu_to_le64(vif->bss_conf.sync_tsf + dtim_offs);
		ctxt_sta->dtim_time =
			cpu_to_le32(vif->bss_conf.sync_device_ts + dtim_offs);

		IWL_DEBUG_INFO(mvm, "DTIM TBTT is 0x%llx/0x%x, offset %d\n",
			       le64_to_cpu(ctxt_sta->dtim_tsf),
			       le32_to_cpu(ctxt_sta->dtim_time),
			       dtim_offs);

		ctxt_sta->is_assoc = cpu_to_le32(1);
	} else {
		ctxt_sta->is_assoc = cpu_to_le32(0);
	}

	ctxt_sta->bi = cpu_to_le32(vif->bss_conf.beacon_int);
	ctxt_sta->bi_reciprocal =
		cpu_to_le32(iwl_mvm_reciprocal(vif->bss_conf.beacon_int));
	ctxt_sta->dtim_interval = cpu_to_le32(vif->bss_conf.beacon_int *
					      vif->bss_conf.dtim_period);
	ctxt_sta->dtim_reciprocal =
		cpu_to_le32(iwl_mvm_reciprocal(vif->bss_conf.beacon_int *
					       vif->bss_conf.dtim_period));

	ctxt_sta->listen_interval = cpu_to_le32(mvm->hw->conf.listen_interval);
	ctxt_sta->assoc_id = cpu_to_le32(vif->bss_conf.aid);
}