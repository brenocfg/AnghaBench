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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct uip_ip_addr {void* addr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DSI ; 
 int /*<<< orphan*/  EX_IABR ; 
 int /*<<< orphan*/  EX_PRG ; 
 int /*<<< orphan*/  EX_TRACE ; 
 scalar_t__ GDBSTUB_DEVICE_USB ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exception_sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  bp_init () ; 
 int /*<<< orphan*/ * current_device ; 
 int /*<<< orphan*/  dbg_exceptionhandler ; 
 int dbg_initialized ; 
 scalar_t__ tcp_gateway ; 
 scalar_t__ tcp_localip ; 
 scalar_t__ tcp_netmask ; 
 int /*<<< orphan*/ * tcpip_init (struct uip_ip_addr*,struct uip_ip_addr*,struct uip_ip_addr*,int /*<<< orphan*/ ) ; 
 void* uip_ipaddr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * usb_init (scalar_t__) ; 

void DEBUG_Init(s32 device_type,s32 channel_port)
{
	u32 level;
	struct uip_ip_addr localip,netmask,gateway;

	UIP_LOG("DEBUG_Init()\n");

	__lwp_thread_dispatchdisable();

	bp_init();

	if(device_type==GDBSTUB_DEVICE_USB) {
		current_device = usb_init(channel_port);
	} else {
		localip.addr = uip_ipaddr((const u8_t*)tcp_localip);
		netmask.addr = uip_ipaddr((const u8_t*)tcp_netmask);
		gateway.addr = uip_ipaddr((const u8_t*)tcp_gateway);

		current_device = tcpip_init(&localip,&netmask,&gateway,(u16)channel_port);
	}

	if(current_device!=NULL) {
		_CPU_ISR_Disable(level);
		__exception_sethandler(EX_DSI,dbg_exceptionhandler);
		__exception_sethandler(EX_PRG,dbg_exceptionhandler);
		__exception_sethandler(EX_TRACE,dbg_exceptionhandler);
		__exception_sethandler(EX_IABR,dbg_exceptionhandler);
		_CPU_ISR_Restore(level);

		dbg_initialized = 1;

	}
	__lwp_thread_dispatchenable();
}