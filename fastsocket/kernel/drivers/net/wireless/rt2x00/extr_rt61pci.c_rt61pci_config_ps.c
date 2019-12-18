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
typedef  int u32 ;
struct rt2x00lib_conf {TYPE_1__* conf; } ;
struct rt2x00_dev {int beacon_int; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;
struct TYPE_2__ {int flags; int listen_interval; } ;

/* Variables and functions */
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  IO_CNTL_CSR ; 
 int /*<<< orphan*/  MAC_CSR11 ; 
 int /*<<< orphan*/  MAC_CSR11_AUTOWAKE ; 
 int /*<<< orphan*/  MAC_CSR11_DELAY_AFTER_TBCN ; 
 int /*<<< orphan*/  MAC_CSR11_TBCN_BEFORE_WAKEUP ; 
 int /*<<< orphan*/  MAC_CSR11_WAKEUP_LATENCY ; 
 int /*<<< orphan*/  MCU_SLEEP ; 
 int /*<<< orphan*/  MCU_WAKEUP ; 
 int /*<<< orphan*/  PCI_USEC_CSR ; 
 int /*<<< orphan*/  SOFT_RESET_CSR ; 
 int STATE_AWAKE ; 
 int STATE_SLEEP ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt61pci_mcu_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt61pci_config_ps(struct rt2x00_dev *rt2x00dev,
				struct rt2x00lib_conf *libconf)
{
	enum dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	if (state == STATE_SLEEP) {
		rt2x00mmio_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN,
				   rt2x00dev->beacon_int - 10);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_interval - 1);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 5);

		/* We must first disable autowake before it can be enabled */
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 1);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_register_write(rt2x00dev, SOFT_RESET_CSR,
					  0x00000005);
		rt2x00mmio_register_write(rt2x00dev, IO_CNTL_CSR, 0x0000001c);
		rt2x00mmio_register_write(rt2x00dev, PCI_USEC_CSR, 0x00000060);

		rt61pci_mcu_request(rt2x00dev, MCU_SLEEP, 0xff, 0, 0);
	} else {
		rt2x00mmio_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 0);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_register_write(rt2x00dev, SOFT_RESET_CSR,
					  0x00000007);
		rt2x00mmio_register_write(rt2x00dev, IO_CNTL_CSR, 0x00000018);
		rt2x00mmio_register_write(rt2x00dev, PCI_USEC_CSR, 0x00000020);

		rt61pci_mcu_request(rt2x00dev, MCU_WAKEUP, 0xff, 0, 0);
	}
}