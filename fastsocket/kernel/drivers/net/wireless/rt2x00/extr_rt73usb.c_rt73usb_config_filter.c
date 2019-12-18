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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  intf_ap_count; } ;

/* Variables and functions */
 unsigned int const FIF_ALLMULTI ; 
 unsigned int const FIF_CONTROL ; 
 unsigned int const FIF_FCSFAIL ; 
 unsigned int const FIF_PLCPFAIL ; 
 unsigned int const FIF_PROMISC_IN_BSS ; 
 unsigned int const FIF_PSPOLL ; 
 int /*<<< orphan*/  TXRX_CSR0 ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_ACK_CTS ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_BROADCAST ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_CONTROL ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_CRC ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_MULTICAST ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_NOT_TO_ME ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_PHYSICAL ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_TO_DS ; 
 int /*<<< orphan*/  TXRX_CSR0_DROP_VERSION_ERROR ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt73usb_config_filter(struct rt2x00_dev *rt2x00dev,
				  const unsigned int filter_flags)
{
	u32 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * and broadcast frames will always be accepted since
	 * there is no filter for it at this time.
	 */
	rt2x00usb_register_read(rt2x00dev, TXRX_CSR0, &reg);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_CRC,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_PHYSICAL,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_CONTROL,
			   !(filter_flags & (FIF_CONTROL | FIF_PSPOLL)));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_NOT_TO_ME,
			   !(filter_flags & FIF_PROMISC_IN_BSS));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_TO_DS,
			   !(filter_flags & FIF_PROMISC_IN_BSS) &&
			   !rt2x00dev->intf_ap_count);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_VERSION_ERROR, 1);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_MULTICAST,
			   !(filter_flags & FIF_ALLMULTI));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_BROADCAST, 0);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_ACK_CTS,
			   !(filter_flags & FIF_CONTROL));
	rt2x00usb_register_write(rt2x00dev, TXRX_CSR0, reg);
}