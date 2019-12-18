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

/* Variables and functions */
 int /*<<< orphan*/  FSA_REF_USB ; 
 int IOSUHAX_FSA_RawOpen (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_fsa_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_fsa_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsaFdUsb ; 
 int usbFd ; 

__attribute__((used)) static bool IOSUHAX_usb_startup(void)
{
    if(!IOSUHAX_disc_io_fsa_open(FSA_REF_USB))
        return false;

    if(usbFd < 0)
    {
        int res = IOSUHAX_FSA_RawOpen(fsaFdUsb, "/dev/usb01", &usbFd);
        if(res < 0)
        {
            res = IOSUHAX_FSA_RawOpen(fsaFdUsb, "/dev/usb02", &usbFd);
            if(res < 0)
            {
                IOSUHAX_disc_io_fsa_close(FSA_REF_USB);
                usbFd = -1;
            }
        }
    }
    return (usbFd >= 0);
}