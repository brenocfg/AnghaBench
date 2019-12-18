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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct wmi_event_swba {int /*<<< orphan*/  tsf; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {int beacon_interval; } ;
struct ath9k_htc_priv {TYPE_1__ cur_beacon_conf; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ATH9K_HTC_MAX_BCN_VIF ; 
 int /*<<< orphan*/  BEACON ; 
 int TSF_TO_TU (int,int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_htc_choose_bslot(struct ath9k_htc_priv *priv,
				  struct wmi_event_swba *swba)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	u64 tsf;
	u32 tsftu;
	u16 intval;
	int slot;

	intval = priv->cur_beacon_conf.beacon_interval;

	tsf = be64_to_cpu(swba->tsf);
	tsftu = TSF_TO_TU(tsf >> 32, tsf);
	slot = ((tsftu % intval) * ATH9K_HTC_MAX_BCN_VIF) / intval;
	slot = ATH9K_HTC_MAX_BCN_VIF - slot - 1;

	ath_dbg(common, BEACON,
		"Choose slot: %d, tsf: %llu, tsftu: %u, intval: %u\n",
		slot, tsf, tsftu, intval);

	return slot;
}