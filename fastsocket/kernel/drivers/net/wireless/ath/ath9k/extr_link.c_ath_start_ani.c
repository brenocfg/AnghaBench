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
typedef  int /*<<< orphan*/  u32 ;
struct ath_softc {TYPE_2__* hw; int /*<<< orphan*/  sc_flags; struct ath_hw* sc_ah; } ;
struct TYPE_8__ {scalar_t__ ani_poll_interval; } ;
struct ath_hw {TYPE_4__ config; } ;
struct TYPE_7__ {unsigned long longcal_timer; unsigned long shortcal_timer; unsigned long checkani_timer; int /*<<< orphan*/  timer; } ;
struct ath_common {TYPE_3__ ani; scalar_t__ disable_ani; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int /*<<< orphan*/  SC_OP_ANI_RUN ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 unsigned long jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath_start_ani(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	unsigned long timestamp = jiffies_to_msecs(jiffies);

	if (common->disable_ani ||
	    !test_bit(SC_OP_ANI_RUN, &sc->sc_flags) ||
	    (sc->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		return;

	common->ani.longcal_timer = timestamp;
	common->ani.shortcal_timer = timestamp;
	common->ani.checkani_timer = timestamp;

	ath_dbg(common, ANI, "Starting ANI\n");
	mod_timer(&common->ani.timer,
		  jiffies + msecs_to_jiffies((u32)ah->config.ani_poll_interval));
}