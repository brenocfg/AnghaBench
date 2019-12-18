#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_7__ {int updated; scalar_t__ noise; scalar_t__ level; scalar_t__ qual; } ;
struct TYPE_5__ {int /*<<< orphan*/  fragment; int /*<<< orphan*/  retries; scalar_t__ misc; int /*<<< orphan*/  code; } ;
struct iw_statistics {TYPE_3__ qual; TYPE_1__ discard; scalar_t__ status; } ;
struct hostap_interface {scalar_t__ type; TYPE_4__* local; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_message_in_bad_msg_fragments; int /*<<< orphan*/  tx_retry_limit_exceeded; scalar_t__ tx_discards_wrong_sa; scalar_t__ rx_discards_no_buffer; scalar_t__ rx_fcs_errors; int /*<<< orphan*/  rx_discards_wep_undecryptable; } ;
struct TYPE_8__ {scalar_t__ iw_mode; scalar_t__ avg_noise; scalar_t__ avg_signal; scalar_t__ comms_qual; TYPE_2__ comm_tallies; struct iw_statistics wstats; } ;
typedef  TYPE_4__ local_info_t ;

/* Variables and functions */
 scalar_t__ HOSTAP_INTERFACE_MAIN ; 
 scalar_t__ IW_MODE_MASTER ; 
 scalar_t__ IW_MODE_REPEAT ; 
 int IW_QUAL_ALL_INVALID ; 
 int IW_QUAL_ALL_UPDATED ; 
 int IW_QUAL_DBM ; 
 scalar_t__ in_atomic () ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ prism2_update_comms_qual (struct net_device*) ; 

__attribute__((used)) static struct iw_statistics *hostap_get_wireless_stats(struct net_device *dev)
{
	struct hostap_interface *iface;
	local_info_t *local;
	struct iw_statistics *wstats;

	iface = netdev_priv(dev);
	local = iface->local;

	/* Why are we doing that ? Jean II */
	if (iface->type != HOSTAP_INTERFACE_MAIN)
		return NULL;

	wstats = &local->wstats;

	wstats->status = 0;
	wstats->discard.code =
		local->comm_tallies.rx_discards_wep_undecryptable;
	wstats->discard.misc =
		local->comm_tallies.rx_fcs_errors +
		local->comm_tallies.rx_discards_no_buffer +
		local->comm_tallies.tx_discards_wrong_sa;

	wstats->discard.retries =
		local->comm_tallies.tx_retry_limit_exceeded;
	wstats->discard.fragment =
		local->comm_tallies.rx_message_in_bad_msg_fragments;

	if (local->iw_mode != IW_MODE_MASTER &&
	    local->iw_mode != IW_MODE_REPEAT) {
		int update = 1;
#ifdef in_atomic
		/* RID reading might sleep and it must not be called in
		 * interrupt context or while atomic. However, this
		 * function seems to be called while atomic (at least in Linux
		 * 2.5.59). Update signal quality values only if in suitable
		 * context. Otherwise, previous values read from tick timer
		 * will be used. */
		if (in_atomic())
			update = 0;
#endif /* in_atomic */

		if (update && prism2_update_comms_qual(dev) == 0)
			wstats->qual.updated = IW_QUAL_ALL_UPDATED |
				IW_QUAL_DBM;

		wstats->qual.qual = local->comms_qual;
		wstats->qual.level = local->avg_signal;
		wstats->qual.noise = local->avg_noise;
	} else {
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
		wstats->qual.updated = IW_QUAL_ALL_INVALID;
	}

	return wstats;
}