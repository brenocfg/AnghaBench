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
typedef  scalar_t__ u32 ;
struct ieee80211_conf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cwm_ignore_extcca; } ;
struct ath_hw {TYPE_2__ config; } ;
struct TYPE_6__ {TYPE_1__* hw; } ;
struct TYPE_4__ {struct ieee80211_conf conf; } ;

/* Variables and functions */
 scalar_t__ AR_2040_JOINED_RX_CLEAR ; 
 int /*<<< orphan*/  AR_2040_MODE ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ conf_is_ht40 (struct ieee80211_conf*) ; 

void ath9k_hw_set11nmac2040(struct ath_hw *ah)
{
	struct ieee80211_conf *conf = &ath9k_hw_common(ah)->hw->conf;
	u32 macmode;

	if (conf_is_ht40(conf) && !ah->config.cwm_ignore_extcca)
		macmode = AR_2040_JOINED_RX_CLEAR;
	else
		macmode = 0;

	REG_WRITE(ah, AR_2040_MODE, macmode);
}