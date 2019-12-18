#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct hw_data {int SurpriseRemove; TYPE_1__ LEDTimer; int /*<<< orphan*/  FragmentThreshold; int /*<<< orphan*/  MaxReceiveLifeTime; } ;
struct wbsoft_priv {struct hw_data sHwData; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FRAGMENT_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_MSDU_LIFE_TIME ; 
 int EINVAL ; 
 int /*<<< orphan*/  Wb35Reg_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Reg_initial (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Rx_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Rx_initial (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Rx_start (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  Wb35Tx_EP2VM_start (struct wbsoft_priv*) ; 
 int /*<<< orphan*/  Wb35Tx_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Tx_initial (struct hw_data*) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  hal_led_control ; 
 int hal_software_set (struct hw_data*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static int hal_init_hardware(struct ieee80211_hw *hw)
{
	struct wbsoft_priv *priv = hw->priv;
	struct hw_data *pHwData = &priv->sHwData;
	u16 SoftwareSet;

	pHwData->MaxReceiveLifeTime = DEFAULT_MSDU_LIFE_TIME;
	pHwData->FragmentThreshold = DEFAULT_FRAGMENT_THRESHOLD;

	if (!Wb35Reg_initial(pHwData))
		goto error_reg_destroy;

	if (!Wb35Tx_initial(pHwData))
		goto error_tx_destroy;

	if (!Wb35Rx_initial(pHwData))
		goto error_rx_destroy;

	init_timer(&pHwData->LEDTimer);
	pHwData->LEDTimer.function = hal_led_control;
	pHwData->LEDTimer.data = (unsigned long)priv;
	pHwData->LEDTimer.expires = jiffies + msecs_to_jiffies(1000);
	add_timer(&pHwData->LEDTimer);

	SoftwareSet = hal_software_set(pHwData);

#ifdef Vendor2
	// Try to make sure the EEPROM contain
	SoftwareSet >>= 8;
	if (SoftwareSet != 0x82)
		return false;
#endif

	Wb35Rx_start(hw);
	Wb35Tx_EP2VM_start(priv);

	return 0;

error_rx_destroy:
	Wb35Rx_destroy(pHwData);
error_tx_destroy:
	Wb35Tx_destroy(pHwData);
error_reg_destroy:
	Wb35Reg_destroy(pHwData);

	pHwData->SurpriseRemove = 1;
	return -EINVAL;
}