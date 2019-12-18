#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int* DeviceRemovable; } ;
struct TYPE_5__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bDescriptorType; int bPwrOn2PwrGood; int bNbrPorts; int bDescLength; TYPE_2__ u; int /*<<< orphan*/  wHubCharacteristics; scalar_t__ bHubContrCurrent; } ;
struct u132 {int num_ports; } ;
struct TYPE_6__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int RH_B_DR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 TYPE_3__ roothub ; 
 int u132_read_pcimem (struct u132*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int u132_roothub_descriptor(struct u132 *u132,
	struct usb_hub_descriptor *desc)
{
	int retval;
	u16 temp;
	u32 rh_a = -1;
	u32 rh_b = -1;
	retval = u132_read_pcimem(u132, roothub.a, &rh_a);
	if (retval)
		return retval;
	desc->bDescriptorType = 0x29;
	desc->bPwrOn2PwrGood = (rh_a & RH_A_POTPGT) >> 24;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = u132->num_ports;
	temp = 1 + (u132->num_ports / 8);
	desc->bDescLength = 7 + 2 * temp;
	temp = 0;
	if (rh_a & RH_A_NPS)
		temp |= 0x0002;
	if (rh_a & RH_A_PSM)
		temp |= 0x0001;
	if (rh_a & RH_A_NOCP)
		temp |= 0x0010;
	else if (rh_a & RH_A_OCPM)
		temp |= 0x0008;
	desc->wHubCharacteristics = cpu_to_le16(temp);
	retval = u132_read_pcimem(u132, roothub.b, &rh_b);
	if (retval)
		return retval;
	memset(desc->u.hs.DeviceRemovable, 0xff,
			sizeof(desc->u.hs.DeviceRemovable));
	desc->u.hs.DeviceRemovable[0] = rh_b & RH_B_DR;
	if (u132->num_ports > 7) {
		desc->u.hs.DeviceRemovable[1] = (rh_b & RH_B_DR) >> 8;
		desc->u.hs.DeviceRemovable[2] = 0xff;
	} else
		desc->u.hs.DeviceRemovable[1] = 0xff;
	return 0;
}