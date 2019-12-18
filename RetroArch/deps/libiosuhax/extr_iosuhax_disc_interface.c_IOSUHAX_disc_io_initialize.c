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
 int fsaFdSd ; 
 int fsaFdUsb ; 
 int initialized ; 
 int sdioFd ; 
 int usbFd ; 

__attribute__((used)) static void IOSUHAX_disc_io_initialize(void)
{
    if(initialized == 0)
    {
        initialized = 1;
        fsaFdSd = -1;
        fsaFdUsb = -1;
        sdioFd = -1;
        usbFd = -1;
    }
}