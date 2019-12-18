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
typedef  int u32 ;
struct rt2x00lib_erp {int basic_rates; int beacon_int; int slot_time; int sifs; int eifs; int /*<<< orphan*/  short_preamble; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int IEEE80211_HEADER ; 
 int /*<<< orphan*/  MAC_CSR8 ; 
 int /*<<< orphan*/  MAC_CSR8_EIFS ; 
 int /*<<< orphan*/  MAC_CSR8_SIFS ; 
 int /*<<< orphan*/  MAC_CSR8_SIFS_AFTER_RX_OFDM ; 
 int /*<<< orphan*/  MAC_CSR9 ; 
 int /*<<< orphan*/  MAC_CSR9_SLOT_TIME ; 
 int /*<<< orphan*/  TXRX_CSR0 ; 
 int /*<<< orphan*/  TXRX_CSR0_RX_ACK_TIMEOUT ; 
 int /*<<< orphan*/  TXRX_CSR0_TSF_OFFSET ; 
 int /*<<< orphan*/  TXRX_CSR4 ; 
 int /*<<< orphan*/  TXRX_CSR4_AUTORESPOND_ENABLE ; 
 int /*<<< orphan*/  TXRX_CSR4_AUTORESPOND_PREAMBLE ; 
 int /*<<< orphan*/  TXRX_CSR5 ; 
 int /*<<< orphan*/  TXRX_CSR9 ; 
 int /*<<< orphan*/  TXRX_CSR9_BEACON_INTERVAL ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt61pci_config_erp(struct rt2x00_dev *rt2x00dev,
			       struct rt2x00lib_erp *erp,
			       u32 changed)
{
	u32 reg;

	rt2x00mmio_register_read(rt2x00dev, TXRX_CSR0, &reg);
	rt2x00_set_field32(&reg, TXRX_CSR0_RX_ACK_TIMEOUT, 0x32);
	rt2x00_set_field32(&reg, TXRX_CSR0_TSF_OFFSET, IEEE80211_HEADER);
	rt2x00mmio_register_write(rt2x00dev, TXRX_CSR0, reg);

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		rt2x00mmio_register_read(rt2x00dev, TXRX_CSR4, &reg);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_PREAMBLE,
				   !!erp->short_preamble);
		rt2x00mmio_register_write(rt2x00dev, TXRX_CSR4, reg);
	}

	if (changed & BSS_CHANGED_BASIC_RATES)
		rt2x00mmio_register_write(rt2x00dev, TXRX_CSR5,
					  erp->basic_rates);

	if (changed & BSS_CHANGED_BEACON_INT) {
		rt2x00mmio_register_read(rt2x00dev, TXRX_CSR9, &reg);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_INTERVAL,
				   erp->beacon_int * 16);
		rt2x00mmio_register_write(rt2x00dev, TXRX_CSR9, reg);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		rt2x00mmio_register_read(rt2x00dev, MAC_CSR9, &reg);
		rt2x00_set_field32(&reg, MAC_CSR9_SLOT_TIME, erp->slot_time);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR9, reg);

		rt2x00mmio_register_read(rt2x00dev, MAC_CSR8, &reg);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS, erp->sifs);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS_AFTER_RX_OFDM, 3);
		rt2x00_set_field32(&reg, MAC_CSR8_EIFS, erp->eifs);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR8, reg);
	}
}