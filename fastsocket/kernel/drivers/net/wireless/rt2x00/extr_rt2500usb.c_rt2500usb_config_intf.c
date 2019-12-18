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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00intf_conf {scalar_t__ type; int sync; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac; } ;
struct rt2x00_intf {int dummy; } ;
struct rt2x00_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int const CONFIG_UPDATE_BSSID ; 
 unsigned int const CONFIG_UPDATE_MAC ; 
 unsigned int const CONFIG_UPDATE_TYPE ; 
 unsigned int GET_DURATION (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_HEADER ; 
 int /*<<< orphan*/  MAC_CSR2 ; 
 int /*<<< orphan*/  MAC_CSR5 ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 unsigned int PREAMBLE ; 
 int /*<<< orphan*/  TXRX_CSR18 ; 
 int /*<<< orphan*/  TXRX_CSR18_OFFSET ; 
 int /*<<< orphan*/  TXRX_CSR19 ; 
 int /*<<< orphan*/  TXRX_CSR19_TSF_SYNC ; 
 int /*<<< orphan*/  TXRX_CSR20 ; 
 int /*<<< orphan*/  TXRX_CSR20_BCN_EXPECT_WINDOW ; 
 int /*<<< orphan*/  TXRX_CSR20_OFFSET ; 
 int /*<<< orphan*/  rt2500usb_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2500usb_config_intf(struct rt2x00_dev *rt2x00dev,
				  struct rt2x00_intf *intf,
				  struct rt2x00intf_conf *conf,
				  const unsigned int flags)
{
	unsigned int bcn_preload;
	u16 reg;

	if (flags & CONFIG_UPDATE_TYPE) {
		/*
		 * Enable beacon config
		 */
		bcn_preload = PREAMBLE + GET_DURATION(IEEE80211_HEADER, 20);
		rt2500usb_register_read(rt2x00dev, TXRX_CSR20, &reg);
		rt2x00_set_field16(&reg, TXRX_CSR20_OFFSET, bcn_preload >> 6);
		rt2x00_set_field16(&reg, TXRX_CSR20_BCN_EXPECT_WINDOW,
				   2 * (conf->type != NL80211_IFTYPE_STATION));
		rt2500usb_register_write(rt2x00dev, TXRX_CSR20, reg);

		/*
		 * Enable synchronisation.
		 */
		rt2500usb_register_read(rt2x00dev, TXRX_CSR18, &reg);
		rt2x00_set_field16(&reg, TXRX_CSR18_OFFSET, 0);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR18, reg);

		rt2500usb_register_read(rt2x00dev, TXRX_CSR19, &reg);
		rt2x00_set_field16(&reg, TXRX_CSR19_TSF_SYNC, conf->sync);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);
	}

	if (flags & CONFIG_UPDATE_MAC)
		rt2500usb_register_multiwrite(rt2x00dev, MAC_CSR2, conf->mac,
					      (3 * sizeof(__le16)));

	if (flags & CONFIG_UPDATE_BSSID)
		rt2500usb_register_multiwrite(rt2x00dev, MAC_CSR5, conf->bssid,
					      (3 * sizeof(__le16)));
}