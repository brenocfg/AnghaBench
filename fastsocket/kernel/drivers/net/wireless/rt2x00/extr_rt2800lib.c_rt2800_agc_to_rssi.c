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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {scalar_t__ curr_band; int lna_gain; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_RSSI_A ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2_OFFSET2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A_OFFSET0 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A_OFFSET1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2_OFFSET2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG_OFFSET0 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG_OFFSET1 ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  RXWI_W2_RSSI0 ; 
 int /*<<< orphan*/  RXWI_W2_RSSI1 ; 
 int /*<<< orphan*/  RXWI_W2_RSSI2 ; 
 int max (int,int) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800_agc_to_rssi(struct rt2x00_dev *rt2x00dev, u32 rxwi_w2)
{
	s8 rssi0 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI0);
	s8 rssi1 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI1);
	s8 rssi2 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI2);
	u16 eeprom;
	u8 offset0;
	u8 offset1;
	u8 offset2;

	if (rt2x00dev->curr_band == IEEE80211_BAND_2GHZ) {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_BG, &eeprom);
		offset0 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG_OFFSET0);
		offset1 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG_OFFSET1);
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_BG2, &eeprom);
		offset2 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG2_OFFSET2);
	} else {
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_A, &eeprom);
		offset0 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A_OFFSET0);
		offset1 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A_OFFSET1);
		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_A2, &eeprom);
		offset2 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A2_OFFSET2);
	}

	/*
	 * Convert the value from the descriptor into the RSSI value
	 * If the value in the descriptor is 0, it is considered invalid
	 * and the default (extremely low) rssi value is assumed
	 */
	rssi0 = (rssi0) ? (-12 - offset0 - rt2x00dev->lna_gain - rssi0) : -128;
	rssi1 = (rssi1) ? (-12 - offset1 - rt2x00dev->lna_gain - rssi1) : -128;
	rssi2 = (rssi2) ? (-12 - offset2 - rt2x00dev->lna_gain - rssi2) : -128;

	/*
	 * mac80211 only accepts a single RSSI value. Calculating the
	 * average doesn't deliver a fair answer either since -60:-60 would
	 * be considered equally good as -50:-70 while the second is the one
	 * which gives less energy...
	 */
	rssi0 = max(rssi0, rssi1);
	return (int)max(rssi0, rssi2);
}