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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  out_buf ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_FSA_GETDEVICEINFO ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iosuhaxHandle ; 
 scalar_t__ memalign (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

int IOSUHAX_FSA_GetDeviceInfo(int fsaFd, const char* device_path, int type, uint32_t* out_data)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!device_path || !out_data)
        return -1;

    const int input_cnt = 3;

    int io_buf_size = sizeof(uint32_t) * input_cnt + strlen(device_path) + 1;

    uint32_t *io_buf = (uint32_t*)memalign(0x20, io_buf_size);
    if(!io_buf)
        return -2;

    io_buf[0] = fsaFd;
    io_buf[1] = sizeof(uint32_t) * input_cnt;
    io_buf[2] = type;
    strcpy(((char*)io_buf) + io_buf[1],  device_path);

    uint32_t out_buf[1 + 0x64 / 4];

    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_FSA_GETDEVICEINFO, io_buf, io_buf_size, out_buf, sizeof(out_buf));
    if(res < 0)
    {
        free(io_buf);
        return res;
    }

    memcpy(out_data, out_buf + 1, 0x64);
    free(io_buf);
    return out_buf[0];
}