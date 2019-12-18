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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00intf_conf {int sync; void** bssid; void** mac; } ;
struct rt2x00_intf {int dummy; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TSF_SYNC ; 
 unsigned int const CONFIG_UPDATE_BSSID ; 
 unsigned int const CONFIG_UPDATE_MAC ; 
 unsigned int const CONFIG_UPDATE_TYPE ; 
 int /*<<< orphan*/  MAC_ADDR_DW0 ; 
 int /*<<< orphan*/  MAC_ADDR_DW1_UNICAST_TO_ME_MASK ; 
 int /*<<< orphan*/  MAC_BSSID_DW0 ; 
 int /*<<< orphan*/  MAC_BSSID_DW1_BSS_BCN_NUM ; 
 int /*<<< orphan*/  MAC_BSSID_DW1_BSS_ID_MASK ; 
 int /*<<< orphan*/  TBTT_SYNC_CFG ; 
 int /*<<< orphan*/  TBTT_SYNC_CFG_BCN_AIFSN ; 
 int /*<<< orphan*/  TBTT_SYNC_CFG_BCN_CWMIN ; 
 int /*<<< orphan*/  TBTT_SYNC_CFG_BCN_EXP_WIN ; 
 int /*<<< orphan*/  TBTT_SYNC_CFG_TBTT_ADJUST ; 
 scalar_t__ TSF_SYNC_AP_NONE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int /*<<< orphan*/  rt2800_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void rt2800_config_intf(struct rt2x00_dev *rt2x00dev, struct rt2x00_intf *intf,
			struct rt2x00intf_conf *conf, const unsigned int flags)
{
	u32 reg;
	bool update_bssid = false;

	if (flags & CONFIG_UPDATE_TYPE) {
		/*
		 * Enable synchronisation.
		 */
		rt2800_register_read(rt2x00dev, BCN_TIME_CFG, &reg);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_SYNC, conf->sync);
		rt2800_register_write(rt2x00dev, BCN_TIME_CFG, reg);

		if (conf->sync == TSF_SYNC_AP_NONE) {
			/*
			 * Tune beacon queue transmit parameters for AP mode
			 */
			rt2800_register_read(rt2x00dev, TBTT_SYNC_CFG, &reg);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_CWMIN, 0);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_AIFSN, 1);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_TBTT_ADJUST, 0);
			rt2800_register_write(rt2x00dev, TBTT_SYNC_CFG, reg);
		} else {
			rt2800_register_read(rt2x00dev, TBTT_SYNC_CFG, &reg);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_CWMIN, 4);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_AIFSN, 2);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_TBTT_ADJUST, 16);
			rt2800_register_write(rt2x00dev, TBTT_SYNC_CFG, reg);
		}
	}

	if (flags & CONFIG_UPDATE_MAC) {
		if (flags & CONFIG_UPDATE_TYPE &&
		    conf->sync == TSF_SYNC_AP_NONE) {
			/*
			 * The BSSID register has to be set to our own mac
			 * address in AP mode.
			 */
			memcpy(conf->bssid, conf->mac, sizeof(conf->mac));
			update_bssid = true;
		}

		if (!is_zero_ether_addr((const u8 *)conf->mac)) {
			reg = le32_to_cpu(conf->mac[1]);
			rt2x00_set_field32(&reg, MAC_ADDR_DW1_UNICAST_TO_ME_MASK, 0xff);
			conf->mac[1] = cpu_to_le32(reg);
		}

		rt2800_register_multiwrite(rt2x00dev, MAC_ADDR_DW0,
					      conf->mac, sizeof(conf->mac));
	}

	if ((flags & CONFIG_UPDATE_BSSID) || update_bssid) {
		if (!is_zero_ether_addr((const u8 *)conf->bssid)) {
			reg = le32_to_cpu(conf->bssid[1]);
			rt2x00_set_field32(&reg, MAC_BSSID_DW1_BSS_ID_MASK, 3);
			rt2x00_set_field32(&reg, MAC_BSSID_DW1_BSS_BCN_NUM, 7);
			conf->bssid[1] = cpu_to_le32(reg);
		}

		rt2800_register_multiwrite(rt2x00dev, MAC_BSSID_DW0,
					      conf->bssid, sizeof(conf->bssid));
	}
}