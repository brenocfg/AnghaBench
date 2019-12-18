#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iwl_priv {TYPE_1__* trans; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBUS_TARG_MEM_RADDR ; 
 int /*<<< orphan*/  HBUS_TARG_MEM_RDAT ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ iwl_read32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (TYPE_1__*,int,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write32 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_ucode_cont_event (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void iwl_print_cont_event_trace(struct iwl_priv *priv, u32 base,
					u32 start_idx, u32 num_events,
					u32 capacity, u32 mode)
{
	u32 i;
	u32 ptr;        /* SRAM byte address of log data */
	u32 ev, time, data; /* event log data */
	unsigned long reg_flags;

	if (mode == 0)
		ptr = base + (4 * sizeof(u32)) + (start_idx * 2 * sizeof(u32));
	else
		ptr = base + (4 * sizeof(u32)) + (start_idx * 3 * sizeof(u32));

	/* Make sure device is powered up for SRAM reads */
	if (!iwl_trans_grab_nic_access(priv->trans, false, &reg_flags))
		return;

	/* Set starting address; reads will auto-increment */
	iwl_write32(priv->trans, HBUS_TARG_MEM_RADDR, ptr);

	/*
	 * Refuse to read more than would have fit into the log from
	 * the current start_idx. This used to happen due to the race
	 * described below, but now WARN because the code below should
	 * prevent it from happening here.
	 */
	if (WARN_ON(num_events > capacity - start_idx))
		num_events = capacity - start_idx;

	/*
	 * "time" is actually "data" for mode 0 (no timestamp).
	 * place event id # at far right for easier visual parsing.
	 */
	for (i = 0; i < num_events; i++) {
		ev = iwl_read32(priv->trans, HBUS_TARG_MEM_RDAT);
		time = iwl_read32(priv->trans, HBUS_TARG_MEM_RDAT);
		if (mode == 0) {
			trace_iwlwifi_dev_ucode_cont_event(
					priv->trans->dev, 0, time, ev);
		} else {
			data = iwl_read32(priv->trans, HBUS_TARG_MEM_RDAT);
			trace_iwlwifi_dev_ucode_cont_event(
					priv->trans->dev, time, data, ev);
		}
	}
	/* Allow device to power down */
	iwl_trans_release_nic_access(priv->trans, &reg_flags);
}