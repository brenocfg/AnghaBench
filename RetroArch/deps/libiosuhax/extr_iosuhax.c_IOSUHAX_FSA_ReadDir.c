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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  directoryEntry_s ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_FSA_READDIR ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iosuhaxHandle ; 
 scalar_t__ memalign (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

int IOSUHAX_FSA_ReadDir(int fsaFd, int handle, directoryEntry_s* out_data)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    if(!out_data)
        return -1;

    const int input_cnt = 2;

    int io_buf_size = sizeof(uint32_t) * input_cnt;

    uint32_t *io_buf = (uint32_t*)memalign(0x20, io_buf_size);
    if(!io_buf)
        return -2;

    io_buf[0] = fsaFd;
    io_buf[1] = handle;

    int result_vec_size = 4 + sizeof(directoryEntry_s);
    uint8_t *result_vec = (uint8_t*) memalign(0x20, result_vec_size);
    if(!result_vec)
    {
        free(io_buf);
        return -2;
    }

    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_FSA_READDIR, io_buf, io_buf_size, result_vec, result_vec_size);
    if(res < 0)
    {
        free(result_vec);
        free(io_buf);
        return res;
    }

    int result = *(int*)result_vec;
    memcpy(out_data, result_vec + 4, sizeof(directoryEntry_s));
    free(io_buf);
    free(result_vec);
    return result;
}