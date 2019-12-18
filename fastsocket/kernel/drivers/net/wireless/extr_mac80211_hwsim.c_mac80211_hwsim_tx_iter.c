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
typedef  int /*<<< orphan*/  u8 ;
struct tx_iter_data {int receive; int /*<<< orphan*/  channel; } ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {TYPE_1__ def; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_chans_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac80211_hwsim_tx_iter(void *_data, u8 *addr,
				   struct ieee80211_vif *vif)
{
	struct tx_iter_data *data = _data;

	if (!vif->chanctx_conf)
		return;

	if (!hwsim_chans_compat(data->channel,
				rcu_dereference(vif->chanctx_conf)->def.chan))
		return;

	data->receive = true;
}