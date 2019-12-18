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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wb35_reg {int SyncIoPause; scalar_t__ EP0vm_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;
struct hw_data {int SurpriseRemove; TYPE_1__ WbUsb; struct wb35_reg reg; } ;

/* Variables and functions */
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 scalar_t__ VM_RUNNING ; 
 scalar_t__ VM_STOP ; 
 int /*<<< orphan*/  Wb35Reg_EP0VM_start (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Reg_Update (struct hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned char
Wb35Reg_ReadSync(  struct hw_data * pHwData,  u16 RegisterNo,   u32 * pRegisterValue )
{
	struct wb35_reg *reg = &pHwData->reg;
	u32 *	pltmp = pRegisterValue;
	int ret = -1;

	// Module shutdown
	if (pHwData->SurpriseRemove)
		return false;

	// Read the register by send usb message------------------------------------

	reg->SyncIoPause = 1;

	// 20060717.5 Wait until EP0VM stop
	while (reg->EP0vm_state != VM_STOP)
		msleep(10);

	reg->EP0vm_state = VM_RUNNING;
	ret = usb_control_msg( pHwData->WbUsb.udev,
			       usb_rcvctrlpipe(pHwData->WbUsb.udev, 0),
			       0x01, USB_TYPE_VENDOR|USB_RECIP_DEVICE|USB_DIR_IN,
			       0x0, RegisterNo, pltmp, 4, HZ*100 );

	*pRegisterValue = cpu_to_le32(*pltmp);

	reg->EP0vm_state = VM_STOP;

	Wb35Reg_Update( pHwData, RegisterNo, *pRegisterValue );
	reg->SyncIoPause = 0;

	Wb35Reg_EP0VM_start( pHwData );

	if (ret < 0) {
		#ifdef _PE_REG_DUMP_
		printk("EP0 Read register usb message sending error\n");
		#endif

		pHwData->SurpriseRemove = 1; // 20060704.2
		return false;
	}

	return true;
}