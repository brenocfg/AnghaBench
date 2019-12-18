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
struct TYPE_2__ {scalar_t__ assoc_id; int /*<<< orphan*/  filter_flags; } ;
struct il_priv {TYPE_1__ staging; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  il_commit_rxon (struct il_priv*) ; 

__attribute__((used)) static inline void
il_set_no_assoc(struct il_priv *il, struct ieee80211_vif *vif)
{
	/*
	 * inform the ucode that there is no longer an
	 * association and that no more packets should be
	 * sent
	 */
	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il->staging.assoc_id = 0;
	il_commit_rxon(il);
}