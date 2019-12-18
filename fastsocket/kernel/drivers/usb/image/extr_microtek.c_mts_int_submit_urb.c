#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
struct urb {int dummy; } ;
struct TYPE_7__ {TYPE_2__* srb; TYPE_1__* instance; } ;
struct TYPE_6__ {int result; } ;
struct TYPE_5__ {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MTS_INT_ERROR (char*,int) ; 
 int /*<<< orphan*/  MTS_INT_INIT () ; 
 TYPE_3__* context ; 
 int /*<<< orphan*/  mts_transfer_cleanup (struct urb*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int,void*,unsigned int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void mts_int_submit_urb (struct urb* transfer,
			int pipe,
			void* data,
			unsigned length,
			usb_complete_t callback )
/* Interrupt context! */

/* Holding transfer->context->lock! */
{
	int res;

	MTS_INT_INIT();

	usb_fill_bulk_urb(transfer,
		      context->instance->usb_dev,
		      pipe,
		      data,
		      length,
		      callback,
		      context
		);

	res = usb_submit_urb( transfer, GFP_ATOMIC );
	if ( unlikely(res) ) {
		MTS_INT_ERROR( "could not submit URB! Error was %d\n",(int)res );
		context->srb->result = DID_ERROR << 16;
		mts_transfer_cleanup(transfer);
	}
	return;
}