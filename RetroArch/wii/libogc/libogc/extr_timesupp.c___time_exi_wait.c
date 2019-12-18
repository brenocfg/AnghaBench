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

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_1 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __time_exi_unlock ; 
 int /*<<< orphan*/  time_exi_wait ; 

__attribute__((used)) static void __time_exi_wait()
{
	u32 ret;

	do {
		if((ret=EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_1,__time_exi_unlock))==1) break;
		LWP_ThreadSleep(time_exi_wait);
	}while(ret==0);
}