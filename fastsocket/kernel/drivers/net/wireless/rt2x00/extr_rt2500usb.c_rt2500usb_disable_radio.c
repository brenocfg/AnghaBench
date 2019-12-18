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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CSR13 ; 
 int /*<<< orphan*/  MAC_CSR14 ; 
 int /*<<< orphan*/  TXRX_CSR19 ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_disable_radio (struct rt2x00_dev*) ; 

__attribute__((used)) static void rt2500usb_disable_radio(struct rt2x00_dev *rt2x00dev)
{
	rt2500usb_register_write(rt2x00dev, MAC_CSR13, 0x2121);
	rt2500usb_register_write(rt2x00dev, MAC_CSR14, 0x2121);

	/*
	 * Disable synchronisation.
	 */
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, 0);

	rt2x00usb_disable_radio(rt2x00dev);
}