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
typedef  int u16 ;
struct omap_ep {int bEndpointAddress; } ;

/* Variables and functions */
 int UDC_EP_DIR ; 
 int /*<<< orphan*/  UDC_EP_NUM ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void use_ep(struct omap_ep *ep, u16 select)
{
	u16	num = ep->bEndpointAddress & 0x0f;

	if (ep->bEndpointAddress & USB_DIR_IN)
		num |= UDC_EP_DIR;
	omap_writew(num | select, UDC_EP_NUM);
	/* when select, MUST deselect later !! */
}