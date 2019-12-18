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
typedef  int u32 ;
struct usb_ftdi {TYPE_1__* udev; } ;
struct TYPE_4__ {int a; int* portstatus; int status; int b; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int FI ; 
 int FIT ; 
 int FSMP (int) ; 
 int OHCI_BLF ; 
 int const OHCI_CONTROL_INIT ; 
 int const OHCI_CTRL_BLE ; 
 int OHCI_CTRL_HCFS ; 
 int OHCI_CTRL_RWC ; 
 int OHCI_HCR ; 
 int OHCI_INTR_FNO ; 
 int OHCI_INTR_INIT ; 
 int OHCI_INTR_MIE ; 
 int OHCI_INTR_OC ; 
 int OHCI_INTR_RD ; 
 int OHCI_INTR_RHSC ; 
 int OHCI_INTR_SF ; 
 int OHCI_INTR_SO ; 
 int OHCI_INTR_UE ; 
 int OHCI_INTR_WDH ; 
 int OHCI_QUIRK_AMD756 ; 
 int OHCI_QUIRK_INITRESET ; 
 int OHCI_QUIRK_SUPERIO ; 
#define  OHCI_USB_OPER 130 
 int OHCI_USB_RESET ; 
#define  OHCI_USB_RESUME 129 
#define  OHCI_USB_SUSPEND 128 
 int RH_A_NDP ; 
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int RH_B_PPCM ; 
 int RH_HS_DRWE ; 
 int RH_HS_LPSC ; 
 int RH_PS_LSDA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ distrust_firmware ; 
 int ed_bulkhead ; 
 int ed_controlhead ; 
 int ftdi_read_pcimem (struct usb_ftdi*,int,int*) ; 
 int ftdi_write_pcimem (struct usb_ftdi*,int,int) ; 
 int hcca ; 
 int intrdisable ; 
 int intrstatus ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__ roothub ; 

__attribute__((used)) static int ftdi_elan_check_controller(struct usb_ftdi *ftdi, int quirk)
{
        int devices = 0;
        int retval;
        u32 hc_control;
        int num_ports;
        u32 control;
        u32 rh_a = -1;
        u32 status;
        u32 fminterval;
        u32 hc_fminterval;
        u32 periodicstart;
        u32 cmdstatus;
        u32 roothub_a;
        int mask = OHCI_INTR_INIT;
        int sleep_time = 0;
        int reset_timeout = 30;        /* ... allow extra time */
        int temp;
        retval = ftdi_write_pcimem(ftdi, intrdisable, OHCI_INTR_MIE);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, control, &control);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, roothub.a, &rh_a);
        if (retval)
                return retval;
        num_ports = rh_a & RH_A_NDP;
        retval = ftdi_read_pcimem(ftdi, fminterval, &hc_fminterval);
        if (retval)
                return retval;
        hc_fminterval &= 0x3fff;
        if (hc_fminterval != FI) {
        }
        hc_fminterval |= FSMP(hc_fminterval) << 16;
        retval = ftdi_read_pcimem(ftdi, control, &hc_control);
        if (retval)
                return retval;
        switch (hc_control & OHCI_CTRL_HCFS) {
        case OHCI_USB_OPER:
                sleep_time = 0;
                break;
        case OHCI_USB_SUSPEND:
        case OHCI_USB_RESUME:
                hc_control &= OHCI_CTRL_RWC;
                hc_control |= OHCI_USB_RESUME;
                sleep_time = 10;
                break;
        default:
                hc_control &= OHCI_CTRL_RWC;
                hc_control |= OHCI_USB_RESET;
                sleep_time = 50;
                break;
        }
        retval = ftdi_write_pcimem(ftdi, control, hc_control);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, control, &control);
        if (retval)
                return retval;
        msleep(sleep_time);
        retval = ftdi_read_pcimem(ftdi, roothub.a, &roothub_a);
        if (retval)
                return retval;
        if (!(roothub_a & RH_A_NPS)) {        /* power down each port */
                for (temp = 0; temp < num_ports; temp++) {
                        retval = ftdi_write_pcimem(ftdi,
                                roothub.portstatus[temp], RH_PS_LSDA);
                        if (retval)
                                return retval;
                }
        }
        retval = ftdi_read_pcimem(ftdi, control, &control);
        if (retval)
                return retval;
      retry:retval = ftdi_read_pcimem(ftdi, cmdstatus, &status);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, cmdstatus, OHCI_HCR);
        if (retval)
                return retval;
      extra:{
                retval = ftdi_read_pcimem(ftdi, cmdstatus, &status);
                if (retval)
                        return retval;
                if (0 != (status & OHCI_HCR)) {
                        if (--reset_timeout == 0) {
                                dev_err(&ftdi->udev->dev, "USB HC reset timed o"
                                        "ut!\n");
                                return -ENODEV;
                        } else {
                                msleep(5);
                                goto extra;
                        }
                }
        }
        if (quirk & OHCI_QUIRK_INITRESET) {
                retval = ftdi_write_pcimem(ftdi, control, hc_control);
                if (retval)
                        return retval;
                retval = ftdi_read_pcimem(ftdi, control, &control);
                if (retval)
                        return retval;
        }
        retval = ftdi_write_pcimem(ftdi, ed_controlhead, 0x00000000);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, ed_bulkhead, 0x11000000);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, hcca, 0x00000000);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, fminterval, &fminterval);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, fminterval,
                ((fminterval & FIT) ^ FIT) | hc_fminterval);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, periodicstart,
                ((9 *hc_fminterval) / 10) & 0x3fff);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, fminterval, &fminterval);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, periodicstart, &periodicstart);
        if (retval)
                return retval;
        if (0 == (fminterval & 0x3fff0000) || 0 == periodicstart) {
                if (!(quirk & OHCI_QUIRK_INITRESET)) {
                        quirk |= OHCI_QUIRK_INITRESET;
                        goto retry;
                } else
                        dev_err(&ftdi->udev->dev, "init err(%08x %04x)\n",
                                fminterval, periodicstart);
        }                        /* start controller operations */
        hc_control &= OHCI_CTRL_RWC;
        hc_control |= OHCI_CONTROL_INIT | OHCI_CTRL_BLE | OHCI_USB_OPER;
        retval = ftdi_write_pcimem(ftdi, control, hc_control);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, cmdstatus, OHCI_BLF);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, cmdstatus, &cmdstatus);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, control, &control);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, roothub.status, RH_HS_DRWE);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, intrstatus, mask);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, intrdisable,
                OHCI_INTR_MIE | OHCI_INTR_OC | OHCI_INTR_RHSC | OHCI_INTR_FNO |
                OHCI_INTR_UE | OHCI_INTR_RD | OHCI_INTR_SF | OHCI_INTR_WDH |
                OHCI_INTR_SO);
        if (retval)
                return retval;        /* handle root hub init quirks ... */
        retval = ftdi_read_pcimem(ftdi, roothub.a, &roothub_a);
        if (retval)
                return retval;
        roothub_a &= ~(RH_A_PSM | RH_A_OCPM);
        if (quirk & OHCI_QUIRK_SUPERIO) {
                roothub_a |= RH_A_NOCP;
                roothub_a &= ~(RH_A_POTPGT | RH_A_NPS);
                retval = ftdi_write_pcimem(ftdi, roothub.a, roothub_a);
                if (retval)
                        return retval;
        } else if ((quirk & OHCI_QUIRK_AMD756) || distrust_firmware) {
                roothub_a |= RH_A_NPS;
                retval = ftdi_write_pcimem(ftdi, roothub.a, roothub_a);
                if (retval)
                        return retval;
        }
        retval = ftdi_write_pcimem(ftdi, roothub.status, RH_HS_LPSC);
        if (retval)
                return retval;
        retval = ftdi_write_pcimem(ftdi, roothub.b,
                (roothub_a & RH_A_NPS) ? 0 : RH_B_PPCM);
        if (retval)
                return retval;
        retval = ftdi_read_pcimem(ftdi, control, &control);
        if (retval)
                return retval;
        mdelay((roothub_a >> 23) & 0x1fe);
        for (temp = 0; temp < num_ports; temp++) {
                u32 portstatus;
                retval = ftdi_read_pcimem(ftdi, roothub.portstatus[temp],
                        &portstatus);
                if (retval)
                        return retval;
                if (1 & portstatus)
                        devices += 1;
        }
        return devices;
}