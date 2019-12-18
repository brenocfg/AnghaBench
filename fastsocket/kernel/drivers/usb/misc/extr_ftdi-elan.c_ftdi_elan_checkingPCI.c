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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int vendor; int device; } ;
struct usb_ftdi {int controlreg; int card_ejected; int function; TYPE_2__ platform_data; TYPE_1__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int ftdi_elan_read_config (struct usb_ftdi*,int,int /*<<< orphan*/ ,int*) ; 
 int ftdi_elan_read_reg (struct usb_ftdi*,int*) ; 

__attribute__((used)) static int ftdi_elan_checkingPCI(struct usb_ftdi *ftdi)
{
        int UxxxStatus = ftdi_elan_read_reg(ftdi, &ftdi->controlreg);
        if (UxxxStatus)
                return UxxxStatus;
        if (ftdi->controlreg & 0x00400000) {
                if (ftdi->card_ejected) {
                } else {
                        ftdi->card_ejected = 1;
                        dev_err(&ftdi->udev->dev, "CARD EJECTED - controlreg = "
                                "%08X\n", ftdi->controlreg);
                }
                return -ENODEV;
        } else {
                u8 fn = ftdi->function - 1;
                int activePCIfn = fn << 8;
                u32 pcidata;
                u32 pciVID;
                u32 pciPID;
                int reg = 0;
                UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                        &pcidata);
                if (UxxxStatus)
                        return UxxxStatus;
                pciVID = pcidata & 0xFFFF;
                pciPID = (pcidata >> 16) & 0xFFFF;
                if (pciVID == ftdi->platform_data.vendor && pciPID ==
                        ftdi->platform_data.device) {
                        return 0;
                } else {
                        dev_err(&ftdi->udev->dev, "vendor=%04X pciVID=%04X devi"
                                "ce=%04X pciPID=%04X\n",
                                ftdi->platform_data.vendor, pciVID,
                                ftdi->platform_data.device, pciPID);
                        return -ENODEV;
                }
        }
}