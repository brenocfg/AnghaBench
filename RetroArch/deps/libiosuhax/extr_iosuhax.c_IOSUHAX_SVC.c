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
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_SVC ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 scalar_t__ iosuhaxHandle ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int IOSUHAX_SVC(uint32_t svc_id, uint32_t * args, uint32_t arg_cnt)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    uint32_t arguments[9];
    arguments[0] = svc_id;

    if(args && arg_cnt)
    {
        if(arg_cnt > 8)
            arg_cnt = 8;

        memcpy(arguments + 1, args, arg_cnt * 4);
    }

    int result;
    int ret = IOS_Ioctl(iosuhaxHandle, IOCTL_SVC, arguments, (1 + arg_cnt) * 4, &result, sizeof(result));
    if(ret < 0)
        return ret;

    return result;
}