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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MEM_READ ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iosuhaxHandle ; 

int IOSUHAX_memread(uint32_t address, uint8_t * out_buffer, uint32_t size)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!out_buffer || !size)
        return -1;

    return IOS_Ioctl(iosuhaxHandle, IOCTL_MEM_READ, &address, sizeof(address), out_buffer, size);
}