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
struct wiphy {int dummy; } ;
struct ath_regulatory {TYPE_1__* regpair; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;
struct TYPE_2__ {int regDmnEnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_reg_apply_active_scan_flags (struct wiphy*,int) ; 
 int /*<<< orphan*/  ath_reg_apply_beaconing_flags (struct wiphy*,int) ; 

__attribute__((used)) static void ath_reg_apply_world_flags(struct wiphy *wiphy,
				      enum nl80211_reg_initiator initiator,
				      struct ath_regulatory *reg)
{
	switch (reg->regpair->regDmnEnum) {
	case 0x60:
	case 0x63:
	case 0x66:
	case 0x67:
	case 0x6C:
		ath_reg_apply_beaconing_flags(wiphy, initiator);
		break;
	case 0x68:
		ath_reg_apply_beaconing_flags(wiphy, initiator);
		ath_reg_apply_active_scan_flags(wiphy, initiator);
		break;
	}
}