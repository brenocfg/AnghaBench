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
struct usb_ftdi {int dummy; } ;

/* Variables and functions */
 int ftdi_elan_check_controller (struct usb_ftdi*,int) ; 
 int ftdi_elan_close_controller (struct usb_ftdi*,int) ; 
 int ftdi_elan_setup_controller (struct usb_ftdi*,int) ; 

__attribute__((used)) static int ftdi_elan_found_controller(struct usb_ftdi *ftdi, int fn, int quirk)
{
        int result;
        int UxxxStatus;
        UxxxStatus = ftdi_elan_setup_controller(ftdi, fn);
        if (UxxxStatus)
                return UxxxStatus;
        result = ftdi_elan_check_controller(ftdi, quirk);
        UxxxStatus = ftdi_elan_close_controller(ftdi, fn);
        if (UxxxStatus)
                return UxxxStatus;
        return result;
}