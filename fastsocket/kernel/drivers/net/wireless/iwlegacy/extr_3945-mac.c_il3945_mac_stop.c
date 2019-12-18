#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rfkill_poll; } ;
struct il_priv {TYPE_1__ _3945; int /*<<< orphan*/  workqueue; scalar_t__ is_open; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int HZ ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_down (struct il_priv*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 

__attribute__((used)) static void
il3945_mac_stop(struct ieee80211_hw *hw)
{
	struct il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	if (!il->is_open) {
		D_MAC80211("leave - skip\n");
		return;
	}

	il->is_open = 0;

	il3945_down(il);

	flush_workqueue(il->workqueue);

	/* start polling the killswitch state again */
	queue_delayed_work(il->workqueue, &il->_3945.rfkill_poll,
			   round_jiffies_relative(2 * HZ));

	D_MAC80211("leave\n");
}