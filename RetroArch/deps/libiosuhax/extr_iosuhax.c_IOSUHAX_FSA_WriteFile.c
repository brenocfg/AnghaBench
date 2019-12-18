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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_FSA_WRITEFILE ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iosuhaxHandle ; 
 scalar_t__ memalign (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

int IOSUHAX_FSA_WriteFile(int fsaFd, const void* data, uint32_t size, uint32_t cnt, int fileHandle, uint32_t flags)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!data)
        return -1;

    const int input_cnt = 5;

    int io_buf_size = ((sizeof(uint32_t) * input_cnt + size * cnt + 0x40) + 0x3F) & ~0x3F;

    uint32_t *io_buf = (uint32_t*)memalign(0x20, io_buf_size);
    if(!io_buf)
        return -2;

    io_buf[0] = fsaFd;
    io_buf[1] = size;
    io_buf[2] = cnt;
    io_buf[3] = fileHandle;
    io_buf[4] = flags;

    /* ! data is put to offset 0x40 to align the buffer input */
    memcpy(((uint8_t*)io_buf) + 0x40, data, size * cnt);

    int result;
    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_FSA_WRITEFILE, io_buf, io_buf_size, &result, sizeof(result));
    if(res < 0)
    {
        free(io_buf);
        return res;
    }
    free(io_buf);
    return result;
}