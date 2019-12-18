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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  io_buf ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MEMCPY ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iosuhaxHandle ; 

int IOSUHAX_memcpy(uint32_t dst, uint32_t src, uint32_t size)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!dst || !src || !size)
      return -1;

    uint32_t io_buf[3];
    io_buf[0] = dst;
    io_buf[1] = src;
    io_buf[2] = size;

    return IOS_Ioctl(iosuhaxHandle, IOCTL_MEMCPY, io_buf, sizeof(io_buf), 0, 0);
}