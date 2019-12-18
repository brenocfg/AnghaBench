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
struct dma_desc {int dummy; } ;
struct TYPE_6__ {int ampdu_density; int ampdu_factor; int /*<<< orphan*/  ampdu_commit_factor; int /*<<< orphan*/  ampdu_commit_density; int /*<<< orphan*/  vif_id; int /*<<< orphan*/  assign_seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  i3e; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct carl9170_tx_superframe {TYPE_3__ s; TYPE_2__ f; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_AMPDU_DENSITY ; 
 int /*<<< orphan*/  AR9170_MAC_AMPDU_FACTOR ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AMPDU_DENSITY ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AMPDU_FACTOR ; 
 int /*<<< orphan*/  MOD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get (int /*<<< orphan*/ ) ; 
 struct carl9170_tx_superframe* get_super (struct dma_desc*) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_assign_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _wlan_tx(struct dma_desc *desc)
{
	struct carl9170_tx_superframe *super = get_super(desc);

	if (unlikely(super->s.assign_seq))
		wlan_assign_seq(&super->f.data.i3e, super->s.vif_id);

	if (unlikely(super->s.ampdu_commit_density)) {
		set(AR9170_MAC_REG_AMPDU_DENSITY,
		    MOD_VAL(AR9170_MAC_AMPDU_DENSITY,
			    get(AR9170_MAC_REG_AMPDU_DENSITY),
			    super->s.ampdu_density));
	}

	if (unlikely(super->s.ampdu_commit_factor)) {
		set(AR9170_MAC_REG_AMPDU_FACTOR,
		    MOD_VAL(AR9170_MAC_AMPDU_FACTOR,
			    get(AR9170_MAC_REG_AMPDU_FACTOR),
			    8 << super->s.ampdu_factor));
	}
}