#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
typedef  void* s64 ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  challange ;
struct TYPE_2__ {int acstart; } ;

/* Variables and functions */
 int BBA_CMD_IRMASKALL ; 
 int BBA_CMD_IRMASKNONE ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 int EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ UIP_ARP_TMRINTERVAL ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  __bba_init (int /*<<< orphan*/ ) ; 
 void* bba_arp_tmr ; 
 int /*<<< orphan*/  bba_calc_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bba_cmd_in8 (int) ; 
 int /*<<< orphan*/  bba_cmd_ins (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bba_cmd_out8 (int,int) ; 
 int /*<<< orphan*/  bba_cmd_outs (int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ bba_device ; 
 int /*<<< orphan*/  bba_interrupt (int*) ; 
 int /*<<< orphan*/  bba_netif ; 
 scalar_t__ diff_msec (void*,void*) ; 
 void* gettime () ; 
 int /*<<< orphan*/  uip_arp_timer () ; 

__attribute__((used)) static void bba_devpoll(u16 *pstatus)
{
	u8 status;
	s64 now;

	UIP_LOG("bba_devpoll()\n");

	now = gettime();
	if(diff_msec(bba_arp_tmr,now)>=UIP_ARP_TMRINTERVAL) {
		uip_arp_timer();
		bba_arp_tmr = gettime();
	}

	status = 0;
	*pstatus = 0;
	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,NULL)==1) {
		status = bba_cmd_in8(0x03);
		if(status) {
			bba_cmd_out8(0x02,BBA_CMD_IRMASKALL);
			if(status&0x80) {
				*pstatus |= (status<<8);
				bba_interrupt(pstatus);
				bba_cmd_out8(0x03,0x80);
				bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
				EXI_Unlock(EXI_CHANNEL_0);
				return;
			}
			if(status&0x40) {
				*pstatus |= (status<<8);
				__bba_init(bba_netif);
				bba_cmd_out8(0x03, 0x40);
				bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
				EXI_Unlock(EXI_CHANNEL_0);
				return;
			}
			if(status&0x20) {
				*pstatus |= (status<<8);
				bba_cmd_out8(0x03, 0x20);
				bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
				EXI_Unlock(EXI_CHANNEL_0);
				return;
			}
			if(status&0x10) {
				u32 response,challange;

				*pstatus |= (status<<8);
				bba_cmd_out8(0x05,bba_device.acstart);
				bba_cmd_ins(0x08,&challange,sizeof(challange));
				response = bba_calc_response(bba_netif,challange);
				bba_cmd_outs(0x09,&response,sizeof(response));
				bba_cmd_out8(0x03, 0x10);
				bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
				EXI_Unlock(EXI_CHANNEL_0);
				return;
			}
			if(status&0x08) {
				*pstatus |= (status<<8);
				bba_cmd_out8(0x03, 0x08);
				bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
				EXI_Unlock(EXI_CHANNEL_0);
				return;
			}

			*pstatus |= (status<<8);
			bba_interrupt(pstatus);
			bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
		}
		EXI_Unlock(EXI_CHANNEL_0);
	}
}