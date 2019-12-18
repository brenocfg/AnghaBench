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
struct dev_state {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 unsigned int USB_RECIP_MASK ; 
 scalar_t__ USB_STATE_ADDRESS ; 
 scalar_t__ USB_STATE_CONFIGURED ; 
 scalar_t__ USB_STATE_UNAUTHENTICATED ; 
 unsigned int USB_TYPE_MASK ; 
 unsigned int USB_TYPE_VENDOR ; 
 int checkintf (struct dev_state*,unsigned int) ; 
 int findintfep (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int check_ctrlrecip(struct dev_state *ps, unsigned int requesttype,
			   unsigned int index)
{
	int ret = 0;

	if (ps->dev->state != USB_STATE_UNAUTHENTICATED
	 && ps->dev->state != USB_STATE_ADDRESS
	 && ps->dev->state != USB_STATE_CONFIGURED)
		return -EHOSTUNREACH;
	if (USB_TYPE_VENDOR == (USB_TYPE_MASK & requesttype))
		return 0;

	index &= 0xff;
	switch (requesttype & USB_RECIP_MASK) {
	case USB_RECIP_ENDPOINT:
		ret = findintfep(ps->dev, index);
		if (ret >= 0)
			ret = checkintf(ps, ret);
		break;

	case USB_RECIP_INTERFACE:
		ret = checkintf(ps, index);
		break;
	}
	return ret;
}