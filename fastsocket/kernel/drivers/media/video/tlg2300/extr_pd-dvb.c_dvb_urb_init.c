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
struct pd_dvb_adapter {int /*<<< orphan*/  ep_addr; TYPE_1__* pd_device; scalar_t__* urb_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_SBUF_NUM ; 
 int /*<<< orphan*/  DVB_URB_BUF_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_bulk_urbs_generic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pd_dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_urb_irq ; 

__attribute__((used)) static int dvb_urb_init(struct pd_dvb_adapter *pd_dvb)
{
	if (pd_dvb->urb_array[0])
		return 0;

	alloc_bulk_urbs_generic(pd_dvb->urb_array, DVB_SBUF_NUM,
			pd_dvb->pd_device->udev, pd_dvb->ep_addr,
			DVB_URB_BUF_SIZE, GFP_KERNEL,
			dvb_urb_irq, pd_dvb);
	return 0;
}