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
typedef  scalar_t__ u16 ;
struct r8a66597_root_hub {int port; } ;
struct r8a66597 {struct r8a66597_root_hub* root_hub; } ;

/* Variables and functions */
 scalar_t__ HSMODE ; 
 scalar_t__ LSMODE ; 
 int USB_PORT_FEAT_ENABLE ; 
 int USB_PORT_FEAT_HIGHSPEED ; 
 int USB_PORT_FEAT_LOWSPEED ; 
 int USB_PORT_FEAT_RESET ; 
 scalar_t__ get_rh_usb_speed (struct r8a66597*,int) ; 

__attribute__((used)) static void r8a66597_usb_connect(struct r8a66597 *r8a66597, int port)
{
	u16 speed = get_rh_usb_speed(r8a66597, port);
	struct r8a66597_root_hub *rh = &r8a66597->root_hub[port];

	rh->port &= ~((1 << USB_PORT_FEAT_HIGHSPEED) |
		      (1 << USB_PORT_FEAT_LOWSPEED));
	if (speed == HSMODE)
		rh->port |= (1 << USB_PORT_FEAT_HIGHSPEED);
	else if (speed == LSMODE)
		rh->port |= (1 << USB_PORT_FEAT_LOWSPEED);

	rh->port &= ~(1 << USB_PORT_FEAT_RESET);
	rh->port |= 1 << USB_PORT_FEAT_ENABLE;
}