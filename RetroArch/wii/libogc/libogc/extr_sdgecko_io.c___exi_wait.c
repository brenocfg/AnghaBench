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
typedef  scalar_t__ u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 scalar_t__ EXI_Lock (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exi_unlock ; 
 int /*<<< orphan*/ * _ioEXILock ; 

__attribute__((used)) static void __exi_wait(s32 drv_no)
{
	u32 ret;

	do {
		if((ret=EXI_Lock(drv_no,EXI_DEVICE_0,__exi_unlock))==1) break;
		LWP_ThreadSleep(_ioEXILock[drv_no]);
	} while(ret==0);
}