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
struct musb {TYPE_1__* xceiv; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  OTG_STATE_A_HOST 140 
#define  OTG_STATE_A_IDLE 139 
#define  OTG_STATE_A_PERIPHERAL 138 
#define  OTG_STATE_A_SUSPEND 137 
#define  OTG_STATE_A_VBUS_ERR 136 
#define  OTG_STATE_A_WAIT_BCON 135 
#define  OTG_STATE_A_WAIT_VFALL 134 
#define  OTG_STATE_A_WAIT_VRISE 133 
#define  OTG_STATE_B_HOST 132 
#define  OTG_STATE_B_IDLE 131 
#define  OTG_STATE_B_PERIPHERAL 130 
#define  OTG_STATE_B_SRP_INIT 129 
#define  OTG_STATE_B_WAIT_ACON 128 

const char *otg_state_string(struct musb *musb)
{
	switch (musb->xceiv->state) {
	case OTG_STATE_A_IDLE:		return "a_idle";
	case OTG_STATE_A_WAIT_VRISE:	return "a_wait_vrise";
	case OTG_STATE_A_WAIT_BCON:	return "a_wait_bcon";
	case OTG_STATE_A_HOST:		return "a_host";
	case OTG_STATE_A_SUSPEND:	return "a_suspend";
	case OTG_STATE_A_PERIPHERAL:	return "a_peripheral";
	case OTG_STATE_A_WAIT_VFALL:	return "a_wait_vfall";
	case OTG_STATE_A_VBUS_ERR:	return "a_vbus_err";
	case OTG_STATE_B_IDLE:		return "b_idle";
	case OTG_STATE_B_SRP_INIT:	return "b_srp_init";
	case OTG_STATE_B_PERIPHERAL:	return "b_peripheral";
	case OTG_STATE_B_WAIT_ACON:	return "b_wait_acon";
	case OTG_STATE_B_HOST:		return "b_host";
	default:			return "UNDEFINED";
	}
}