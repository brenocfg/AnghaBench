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
typedef  int /*<<< orphan*/  fsaFd ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_FSA_OPEN ; 
 int IOS_Ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ iosuhaxHandle ; 

int IOSUHAX_FSA_Open(void)
{
    if(iosuhaxHandle < 0)
        return iosuhaxHandle;

    int fsaFd;

    int res = IOS_Ioctl(iosuhaxHandle, IOCTL_FSA_OPEN, 0, 0, &fsaFd, sizeof(fsaFd));
    if(res < 0)
        return res;

    return fsaFd;
}