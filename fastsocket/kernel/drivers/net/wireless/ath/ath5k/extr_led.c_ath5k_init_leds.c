#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct ath5k_hw {int /*<<< orphan*/  tx_led; int /*<<< orphan*/  rx_led; int /*<<< orphan*/  status; int /*<<< orphan*/  led_on; int /*<<< orphan*/  led_pin; struct pci_dev* pdev; struct ieee80211_hw* hw; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_LED_MAX_NAME_LEN ; 
 int /*<<< orphan*/  ATH_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_POLARITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_STAT_LEDSOFT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ath5k_led_devices ; 
 int /*<<< orphan*/  ath5k_led_enable (struct ath5k_hw*) ; 
 int ath5k_register_led (struct ath5k_hw*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_rx_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_tx_led_name (struct ieee80211_hw*) ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

int ath5k_init_leds(struct ath5k_hw *ah)
{
	int ret = 0;
	struct ieee80211_hw *hw = ah->hw;
#ifndef CONFIG_ATHEROS_AR231X
	struct pci_dev *pdev = ah->pdev;
#endif
	char name[ATH5K_LED_MAX_NAME_LEN + 1];
	const struct pci_device_id *match;

	if (!ah->pdev)
		return 0;

#ifdef CONFIG_ATHEROS_AR231X
	match = NULL;
#else
	match = pci_match_id(&ath5k_led_devices[0], pdev);
#endif
	if (match) {
		__set_bit(ATH_STAT_LEDSOFT, ah->status);
		ah->led_pin = ATH_PIN(match->driver_data);
		ah->led_on = ATH_POLARITY(match->driver_data);
	}

	if (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		goto out;

	ath5k_led_enable(ah);

	snprintf(name, sizeof(name), "ath5k-%s::rx", wiphy_name(hw->wiphy));
	ret = ath5k_register_led(ah, &ah->rx_led, name,
		ieee80211_get_rx_led_name(hw));
	if (ret)
		goto out;

	snprintf(name, sizeof(name), "ath5k-%s::tx", wiphy_name(hw->wiphy));
	ret = ath5k_register_led(ah, &ah->tx_led, name,
		ieee80211_get_tx_led_name(hw));
out:
	return ret;
}