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
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_local {unsigned int filter_flags; int /*<<< orphan*/  filter_lock; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  mc_count; scalar_t__ fif_pspoll; scalar_t__ fif_other_bss; scalar_t__ fif_control; scalar_t__ fif_plcpfail; scalar_t__ fif_fcsfail; scalar_t__ probe_req_reg; scalar_t__ fif_probe_req; int /*<<< orphan*/  scanning; scalar_t__ monitors; int /*<<< orphan*/  iff_allmultis; int /*<<< orphan*/  iff_promiscs; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PLCPFAIL ; 
 unsigned int FIF_PROBE_REQ ; 
 unsigned int FIF_PROMISC_IN_BSS ; 
 unsigned int FIF_PSPOLL ; 
 int /*<<< orphan*/  SCAN_ONCHANNEL_SCANNING ; 
 int /*<<< orphan*/  SCAN_SW_SCANNING ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_configure_filter (struct ieee80211_local*,unsigned int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_prepare_multicast (struct ieee80211_local*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_configure_filter(struct ieee80211_local *local)
{
	u64 mc;
	unsigned int changed_flags;
	unsigned int new_flags = 0;

	if (atomic_read(&local->iff_promiscs))
		new_flags |= FIF_PROMISC_IN_BSS;

	if (atomic_read(&local->iff_allmultis))
		new_flags |= FIF_ALLMULTI;

	if (local->monitors || test_bit(SCAN_SW_SCANNING, &local->scanning) ||
	    test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning))
		new_flags |= FIF_BCN_PRBRESP_PROMISC;

	if (local->fif_probe_req || local->probe_req_reg)
		new_flags |= FIF_PROBE_REQ;

	if (local->fif_fcsfail)
		new_flags |= FIF_FCSFAIL;

	if (local->fif_plcpfail)
		new_flags |= FIF_PLCPFAIL;

	if (local->fif_control)
		new_flags |= FIF_CONTROL;

	if (local->fif_other_bss)
		new_flags |= FIF_OTHER_BSS;

	if (local->fif_pspoll)
		new_flags |= FIF_PSPOLL;

	spin_lock_bh(&local->filter_lock);
	changed_flags = local->filter_flags ^ new_flags;

#if 0 /* Not in RHEL */
	mc = drv_prepare_multicast(local, &local->mc_list);
#else
	mc = drv_prepare_multicast(local, local->mc_count, local->mc_list);
#endif
	spin_unlock_bh(&local->filter_lock);

	/* be a bit nasty */
	new_flags |= (1<<31);

	drv_configure_filter(local, changed_flags, &new_flags, mc);

	WARN_ON(new_flags & (1<<31));

	local->filter_flags = new_flags & ~(1<<31);
}