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
typedef  int u8 ;
struct st5481_intr {int /*<<< orphan*/  urb; } ;
struct st5481_adapter {int leds; struct st5481_intr intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
#define  DCOLL_INT 143 
#define  DEN_INT 142 
#define  FFCTRH_OUT_B1 141 
#define  FFCTRH_OUT_B2 140 
#define  FFCTRL_OUT_B1 139 
#define  FFCTRL_OUT_B2 138 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GPIO_DIR 137 
#define  GPIO_OUT 136 
#define  MPMSK 135 
#define  RED_LED 134 
#define  RXCI_INT 133 
#define  SDA_MAX 132 
#define  SDA_MIN 131 
#define  SDELAY_VALUE 130 
#define  SET_DEFAULT 129 
 int /*<<< orphan*/  ST5481_CMD_PUP ; 
#define  STT 128 
 int /*<<< orphan*/  SUBMIT_URB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st5481_ph_command (struct st5481_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void st5481_start(struct st5481_adapter *adapter)
{
	static const u8 init_cmd_table[]={
		SET_DEFAULT,0,
		STT,0,
		SDA_MIN,0x0d,
		SDA_MAX,0x29,
		SDELAY_VALUE,0x14,
		GPIO_DIR,0x01,		
		GPIO_OUT,RED_LED,
//		FFCTRL_OUT_D,4,
//		FFCTRH_OUT_D,12,
		FFCTRL_OUT_B1,6,
		FFCTRH_OUT_B1,20,
		FFCTRL_OUT_B2,6,
		FFCTRH_OUT_B2,20,
		MPMSK,RXCI_INT+DEN_INT+DCOLL_INT,
		0
	};	
	struct st5481_intr *intr = &adapter->intr;
	int i = 0;
	u8 request,value;

	DBG(8,"");

	adapter->leds = RED_LED; 

	// Start receiving on the interrupt endpoint
	SUBMIT_URB(intr->urb, GFP_KERNEL); 

	while ((request = init_cmd_table[i++])) {
		value = init_cmd_table[i++];
		st5481_usb_device_ctrl_msg(adapter, request, value, NULL, NULL);
	}
	st5481_ph_command(adapter, ST5481_CMD_PUP);
}