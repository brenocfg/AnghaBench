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
struct wb_usb {scalar_t__ DetectCount; } ;
struct wb35_reg {scalar_t__ EP0vm_state; } ;
struct hw_data {int /*<<< orphan*/  SurpriseRemove; struct wb_usb WbUsb; struct wb35_reg reg; } ;

/* Variables and functions */
 scalar_t__ VM_STOP ; 

__attribute__((used)) static unsigned char hal_idle(struct hw_data *pHwData)
{
	struct wb35_reg *reg = &pHwData->reg;
	struct wb_usb *pWbUsb = &pHwData->WbUsb;

	if (!pHwData->SurpriseRemove
	    && (pWbUsb->DetectCount || reg->EP0vm_state != VM_STOP))
		return false;

	return true;
}