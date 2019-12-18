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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MEM_WRITE ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ iosuhaxHandle ; 
 scalar_t__ memalign (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/  const*,scalar_t__) ; 

int IOSUHAX_memwrite(uint32_t address, const uint8_t * buffer, uint32_t size)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!buffer)
        return -1;

    uint32_t *io_buf = (uint32_t*)memalign(0x20, size + 4);
    if(!io_buf)
        return -2;

    io_buf[0] = address;
    memcpy(io_buf + 1, buffer, size);

    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_MEM_WRITE, io_buf, size + 4, 0, 0);

    free(io_buf);
    return res;
}