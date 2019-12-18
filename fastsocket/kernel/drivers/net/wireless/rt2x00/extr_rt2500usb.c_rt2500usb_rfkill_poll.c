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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CSR19 ; 
 int /*<<< orphan*/  MAC_CSR19_VAL7 ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_rfkill_poll(struct rt2x00_dev *rt2x00dev)
{
	u16 reg;

	rt2500usb_register_read(rt2x00dev, MAC_CSR19, &reg);
	return rt2x00_get_field16(reg, MAC_CSR19_VAL7);
}