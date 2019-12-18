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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int IOSUHAX_FSA_RawWrite (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOSUHAX_usb_isInserted () ; 
 int /*<<< orphan*/  fsaFdUsb ; 
 int /*<<< orphan*/  usbFd ; 

__attribute__((used)) static bool IOSUHAX_usb_writeSectors(uint32_t sector, uint32_t numSectors, const void* buffer)
{
    if(!IOSUHAX_usb_isInserted() || !buffer)
        return false;

    int res = IOSUHAX_FSA_RawWrite(fsaFdUsb, buffer, 512, numSectors, sector, usbFd);
    if(res < 0)
    {
        return false;
    }

    return true;
}