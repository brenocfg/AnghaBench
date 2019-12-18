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

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_FSA_READFILE ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iosuhaxHandle ; 
 scalar_t__ memalign (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

int IOSUHAX_FSA_ReadFile(int fsaFd, void* data, uint32_t size, uint32_t cnt, int fileHandle, uint32_t flags)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!data)
        return -1;

    const int input_cnt = 5;

    int io_buf_size = sizeof(uint32_t) * input_cnt;

    uint32_t *io_buf = (uint32_t*)memalign(0x20, io_buf_size);
    if(!io_buf)
        return -2;

    io_buf[0] = fsaFd;
    io_buf[1] = size;
    io_buf[2] = cnt;
    io_buf[3] = fileHandle;
    io_buf[4] = flags;

    int out_buf_size = ((size * cnt + 0x40) + 0x3F) & ~0x3F;

    uint32_t *out_buffer = (uint32_t*)memalign(0x40, out_buf_size);
    if(!out_buffer)
    {
        free(io_buf);
        return -2;
    }

    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_FSA_READFILE, io_buf, io_buf_size, out_buffer, out_buf_size);
    if(res < 0)
    {
        free(out_buffer);
        free(io_buf);
        return res;
    }

    /* ! data is put to offset 0x40 to align the buffer output */
    memcpy(data, ((uint8_t*)out_buffer) + 0x40, size * cnt);

    int result = out_buffer[0];

    free(out_buffer);
    free(io_buf);
    return result;
}