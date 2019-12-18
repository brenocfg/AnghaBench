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
struct TYPE_2__ {int dma_beacon_response_time; int sw_beacon_response_time; int ack_6mb; int analog_shiftreg; int enable_ani; int rx_intr_mitigation; int pcieSerDesWrite; int /*<<< orphan*/  serialize_regmode; void*** spurchans; scalar_t__ pcie_waen; scalar_t__ pcie_clock_req; scalar_t__ cwm_ignore_extcca; scalar_t__ additional_swba_backoff; } ;
struct ath_hw {TYPE_1__ config; } ;

/* Variables and functions */
 int AR_EEPROM_MODAL_SPURS ; 
 void* AR_NO_SPUR ; 
 int /*<<< orphan*/  SER_REG_MODE_AUTO ; 
 int num_possible_cpus () ; 

__attribute__((used)) static void ath9k_hw_init_config(struct ath_hw *ah)
{
	int i;

	ah->config.dma_beacon_response_time = 1;
	ah->config.sw_beacon_response_time = 6;
	ah->config.additional_swba_backoff = 0;
	ah->config.ack_6mb = 0x0;
	ah->config.cwm_ignore_extcca = 0;
	ah->config.pcie_clock_req = 0;
	ah->config.pcie_waen = 0;
	ah->config.analog_shiftreg = 1;
	ah->config.enable_ani = true;

	for (i = 0; i < AR_EEPROM_MODAL_SPURS; i++) {
		ah->config.spurchans[i][0] = AR_NO_SPUR;
		ah->config.spurchans[i][1] = AR_NO_SPUR;
	}

	ah->config.rx_intr_mitigation = true;
	ah->config.pcieSerDesWrite = true;

	/*
	 * We need this for PCI devices only (Cardbus, PCI, miniPCI)
	 * _and_ if on non-uniprocessor systems (Multiprocessor/HT).
	 * This means we use it for all AR5416 devices, and the few
	 * minor PCI AR9280 devices out there.
	 *
	 * Serialization is required because these devices do not handle
	 * well the case of two concurrent reads/writes due to the latency
	 * involved. During one read/write another read/write can be issued
	 * on another CPU while the previous read/write may still be working
	 * on our hardware, if we hit this case the hardware poops in a loop.
	 * We prevent this by serializing reads and writes.
	 *
	 * This issue is not present on PCI-Express devices or pre-AR5416
	 * devices (legacy, 802.11abg).
	 */
	if (num_possible_cpus() > 1)
		ah->config.serialize_regmode = SER_REG_MODE_AUTO;
}