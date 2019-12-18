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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  status; } ;
struct cx231xx {int state; TYPE_1__* dvb; } ;
struct TYPE_2__ {int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_err_status (struct cx231xx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dvb_bulk_copy(struct cx231xx *dev, struct urb *urb)
{
	if (!dev)
		return 0;

	if ((dev->state & DEV_DISCONNECTED) || (dev->state & DEV_MISCONFIGURED))
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	/* Feed the transport payload into the kernel demux */
	dvb_dmx_swfilter(&dev->dvb->demux,
		urb->transfer_buffer, urb->actual_length);

	return 0;
}