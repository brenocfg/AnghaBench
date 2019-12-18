#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bba_priv {int acstart; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  challange ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int BBA_CMD_IRMASKALL ; 
 int BBA_CMD_IRMASKNONE ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (int,int)) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  LWIP_ERROR (char*) ; 
 int NETIF_DEBUG ; 
 int /*<<< orphan*/  __bba_init (TYPE_1__*) ; 
 int /*<<< orphan*/  bba_calc_response (struct bba_priv*,int /*<<< orphan*/ ) ; 
 int bba_cmd_in8 (int) ; 
 int /*<<< orphan*/  bba_cmd_ins (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bba_cmd_out8 (int,int) ; 
 int /*<<< orphan*/  bba_cmd_outs (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bba_interrupt (TYPE_1__*) ; 
 TYPE_1__* gc_netif ; 

__attribute__((used)) static s32 bba_event_handler(s32 nChn,s32 nDev)
{
	u8 status;
	struct bba_priv *priv = (struct bba_priv*)gc_netif->state;

	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,bba_event_handler)==0) {
		LWIP_DEBUGF(NETIF_DEBUG|1,("bba_event_handler(exi locked)\n"));
		return 1;
	}

	status = bba_cmd_in8(0x03);
	bba_cmd_out8(0x02,BBA_CMD_IRMASKALL);

	LWIP_DEBUGF(NETIF_DEBUG,("bba_event_handler(status(%02x))\n",status));

	if(status&0x80) {
		LWIP_DEBUGF(NETIF_DEBUG,("bba_event_handler(bba_interrupt(%02x))\n",status));
		bba_interrupt(gc_netif);
		bba_cmd_out8(0x03,0x80);
		bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
		EXI_Unlock(EXI_CHANNEL_0);
		return 1;
	}
	if(status&0x40) {
		LWIP_ERROR(("bba_event_handler(bba_reset(%02x))\n",status));
		__bba_init(gc_netif);
		bba_cmd_out8(0x03, 0x40);
		bba_cmd_out8(0x02, BBA_CMD_IRMASKNONE);
		EXI_Unlock(EXI_CHANNEL_0);
		return 1;
	}
	if(status&0x20) {
		LWIP_DEBUGF(NETIF_DEBUG,("bba_event_handler(unknown(%02x))\n",status));
		bba_cmd_out8(0x03, 0x20);
		bba_cmd_out8(0x02, BBA_CMD_IRMASKNONE);
		EXI_Unlock(EXI_CHANNEL_0);
		return 1;
	}
	if(status&0x10) {
		u32 response,challange;
		LWIP_DEBUGF(NETIF_DEBUG,("bba_event_handler(challange/response(%02x))\n",status));
		bba_cmd_out8(0x05,priv->acstart);
		bba_cmd_ins(0x08,&challange,sizeof(challange));
		response = bba_calc_response(priv,challange);
		bba_cmd_outs(0x09,&response,sizeof(response));

		bba_cmd_out8(0x03, 0x10);
		bba_cmd_out8(0x02, BBA_CMD_IRMASKNONE);
		EXI_Unlock(EXI_CHANNEL_0);
		return 1;
	}
	if(status&0x08) {
		LWIP_DEBUGF(NETIF_DEBUG,("bba_event_handler(challange/response status(%02x))\n",bba_cmd_in8(0x0b)));
		bba_cmd_out8(0x03, 0x08);
		bba_cmd_out8(0x02, BBA_CMD_IRMASKNONE);
		EXI_Unlock(EXI_CHANNEL_0);
		return 1;
	}
	LWIP_ERROR(("GCIF - EXI - ?? %02x\n", status));
	bba_interrupt(gc_netif);
	bba_cmd_out8(0x02,BBA_CMD_IRMASKNONE);
	EXI_Unlock(EXI_CHANNEL_0);
	return 1;
}