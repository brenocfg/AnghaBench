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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00lib_conf {TYPE_1__* conf; } ;
struct rt2x00_dev {int beacon_int; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;
struct TYPE_2__ {int flags; int listen_interval; } ;

/* Variables and functions */
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  MAC_CSR11 ; 
 int /*<<< orphan*/  MAC_CSR11_AUTOWAKE ; 
 int /*<<< orphan*/  MAC_CSR11_DELAY_AFTER_TBCN ; 
 int /*<<< orphan*/  MAC_CSR11_TBCN_BEFORE_WAKEUP ; 
 int /*<<< orphan*/  MAC_CSR11_WAKEUP_LATENCY ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 int STATE_AWAKE ; 
 int STATE_SLEEP ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int /*<<< orphan*/  USB_MODE_SLEEP ; 
 int /*<<< orphan*/  USB_MODE_WAKEUP ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt73usb_config_ps(struct rt2x00_dev *rt2x00dev,
				struct rt2x00lib_conf *libconf)
{
	enum dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	if (state == STATE_SLEEP) {
		rt2x00usb_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN,
				   rt2x00dev->beacon_int - 10);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_interval - 1);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 5);

		/* We must first disable autowake before it can be enabled */
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00usb_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 1);
		rt2x00usb_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
					    USB_MODE_SLEEP, REGISTER_TIMEOUT);
	} else {
		rt2x00usb_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 0);
		rt2x00usb_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
					    USB_MODE_WAKEUP, REGISTER_TIMEOUT);
	}
}