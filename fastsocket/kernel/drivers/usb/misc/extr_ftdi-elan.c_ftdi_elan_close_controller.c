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
typedef  int u32 ;
struct usb_ftdi {int dummy; } ;

/* Variables and functions */
 int ftdi_elan_read_config (struct usb_ftdi*,int,int /*<<< orphan*/ ,int*) ; 
 int ftdi_elan_write_config (struct usb_ftdi*,int,int,int) ; 
 int ftdi_elan_write_reg (struct usb_ftdi*,int) ; 

__attribute__((used)) static int ftdi_elan_close_controller(struct usb_ftdi *ftdi, int fn)
{
        u32 latence_timer;
        int UxxxStatus;
        u32 pcidata;
        int reg = 0;
        int activePCIfn = fn << 8;
        UxxxStatus = ftdi_elan_write_reg(ftdi, 0x0000025FL | 0x2800);
        if (UxxxStatus)
                return UxxxStatus;
        reg = 16;
        UxxxStatus = ftdi_elan_write_config(ftdi, activePCIfn | reg, 0,
                0xFFFFFFFF);
        if (UxxxStatus)
                return UxxxStatus;
        UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                &pcidata);
        if (UxxxStatus)
                return UxxxStatus;
        UxxxStatus = ftdi_elan_write_config(ftdi, activePCIfn | reg, 0,
                0x00000000);
        if (UxxxStatus)
                return UxxxStatus;
        UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                &pcidata);
        if (UxxxStatus)
                return UxxxStatus;
        reg = 12;
        UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                &latence_timer);
        if (UxxxStatus)
                return UxxxStatus;
        latence_timer &= 0xFFFF00FF;
        latence_timer |= 0x00001600;
        UxxxStatus = ftdi_elan_write_config(ftdi, activePCIfn | reg, 0x00,
                latence_timer);
        if (UxxxStatus)
                return UxxxStatus;
        UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                &pcidata);
        if (UxxxStatus)
                return UxxxStatus;
        reg = 4;
        UxxxStatus = ftdi_elan_write_config(ftdi, activePCIfn | reg, 0x00,
                0x00);
        if (UxxxStatus)
                return UxxxStatus;
        UxxxStatus = ftdi_elan_read_config(ftdi, activePCIfn | reg, 0,
                &pcidata);
        if (UxxxStatus)
                return UxxxStatus;
        return 0;
}