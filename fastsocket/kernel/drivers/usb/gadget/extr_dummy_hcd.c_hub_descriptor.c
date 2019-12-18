#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* DeviceRemovable; } ;
struct TYPE_3__ {TYPE_2__ hs; } ;
struct usb_hub_descriptor {int bDescriptorType; int bDescLength; int bNbrPorts; TYPE_1__ u; int /*<<< orphan*/  wHubCharacteristics; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct usb_hub_descriptor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
hub_descriptor (struct usb_hub_descriptor *desc)
{
	memset (desc, 0, sizeof *desc);
	desc->bDescriptorType = 0x29;
	desc->bDescLength = 9;
	desc->wHubCharacteristics = cpu_to_le16(0x0001);
	desc->bNbrPorts = 1;
	desc->u.hs.DeviceRemovable[0] = 0xff;
	desc->u.hs.DeviceRemovable[1] = 0xff;
}