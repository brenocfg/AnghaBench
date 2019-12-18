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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 scalar_t__ EXI_Lock (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __usbgecko_exi_unlock ; 
 int /*<<< orphan*/  __usbgecko_init () ; 
 int /*<<< orphan*/  usbgecko_inited ; 
 int /*<<< orphan*/ * wait_exi_queue ; 

__attribute__((used)) static __inline__ void __usbgecko_exi_wait(s32 chn)
{
	u32 level;

	_CPU_ISR_Disable(level);
	if(!usbgecko_inited) __usbgecko_init();
	while(EXI_Lock(chn,EXI_DEVICE_0,__usbgecko_exi_unlock)==0) {
		LWP_ThreadSleep(wait_exi_queue[chn]);
	}
	_CPU_ISR_Restore(level);
}