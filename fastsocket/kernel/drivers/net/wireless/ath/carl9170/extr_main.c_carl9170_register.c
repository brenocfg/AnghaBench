#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ath_regulatory {int /*<<< orphan*/  alpha2; } ;
struct TYPE_13__ {int vif_num; int /*<<< orphan*/  mem_blocks; } ;
struct TYPE_10__ {struct ath_regulatory regulatory; } ;
struct ar9170 {int registered; TYPE_7__* hw; TYPE_6__* udev; TYPE_5__* vif_priv; TYPE_4__ fw; int /*<<< orphan*/  mem_bitmap; TYPE_1__ common; } ;
struct TYPE_11__ {int ht_supported; } ;
struct TYPE_18__ {TYPE_2__ ht_cap; } ;
struct TYPE_12__ {int ht_supported; } ;
struct TYPE_17__ {TYPE_3__ ht_cap; } ;
struct TYPE_16__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int id; int /*<<< orphan*/ * vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_is_world_regd (struct ath_regulatory*) ; 
 int ath_regd_init (struct ath_regulatory*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ carl9170_band_2GHz ; 
 TYPE_8__ carl9170_band_5GHz ; 
 int /*<<< orphan*/  carl9170_debugfs_register (struct ar9170*) ; 
 int carl9170_led_init (struct ar9170*) ; 
 int carl9170_led_register (struct ar9170*) ; 
 int carl9170_parse_eeprom (struct ar9170*) ; 
 int carl9170_read_eeprom (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_reg_notifier ; 
 int carl9170_register_hwrng (struct ar9170*) ; 
 int carl9170_register_wps_button (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_unregister (struct ar9170*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ieee80211_register_hw (TYPE_7__*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ modparam_noht ; 
 int /*<<< orphan*/  regulatory_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

int carl9170_register(struct ar9170 *ar)
{
	struct ath_regulatory *regulatory = &ar->common.regulatory;
	int err = 0, i;

	if (WARN_ON(ar->mem_bitmap))
		return -EINVAL;

	ar->mem_bitmap = kzalloc(roundup(ar->fw.mem_blocks, BITS_PER_LONG) *
				 sizeof(unsigned long), GFP_KERNEL);

	if (!ar->mem_bitmap)
		return -ENOMEM;

	/* try to read EEPROM, init MAC addr */
	err = carl9170_read_eeprom(ar);
	if (err)
		return err;

	err = carl9170_parse_eeprom(ar);
	if (err)
		return err;

	err = ath_regd_init(regulatory, ar->hw->wiphy,
			    carl9170_reg_notifier);
	if (err)
		return err;

	if (modparam_noht) {
		carl9170_band_2GHz.ht_cap.ht_supported = false;
		carl9170_band_5GHz.ht_cap.ht_supported = false;
	}

	for (i = 0; i < ar->fw.vif_num; i++) {
		ar->vif_priv[i].id = i;
		ar->vif_priv[i].vif = NULL;
	}

	err = ieee80211_register_hw(ar->hw);
	if (err)
		return err;

	/* mac80211 interface is now registered */
	ar->registered = true;

	if (!ath_is_world_regd(regulatory))
		regulatory_hint(ar->hw->wiphy, regulatory->alpha2);

#ifdef CONFIG_CARL9170_DEBUGFS
	carl9170_debugfs_register(ar);
#endif /* CONFIG_CARL9170_DEBUGFS */

	err = carl9170_led_init(ar);
	if (err)
		goto err_unreg;

#ifdef CONFIG_CARL9170_LEDS
	err = carl9170_led_register(ar);
	if (err)
		goto err_unreg;
#endif /* CONFIG_CARL9170_LEDS */

#ifdef CONFIG_CARL9170_WPC
	err = carl9170_register_wps_button(ar);
	if (err)
		goto err_unreg;
#endif /* CONFIG_CARL9170_WPC */

#ifdef CONFIG_CARL9170_HWRNG
	err = carl9170_register_hwrng(ar);
	if (err)
		goto err_unreg;
#endif /* CONFIG_CARL9170_HWRNG */

	dev_info(&ar->udev->dev, "Atheros AR9170 is registered as '%s'\n",
		 wiphy_name(ar->hw->wiphy));

	return 0;

err_unreg:
	carl9170_unregister(ar);
	return err;
}