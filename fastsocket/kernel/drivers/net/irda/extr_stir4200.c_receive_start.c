#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  in_frame; } ;
struct stir_cb {int receiving; TYPE_2__* rx_urb; TYPE_1__ rx_buff; } ;
struct TYPE_4__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OUTSIDE_FRAME ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int receive_start(struct stir_cb *stir)
{
	/* reset state */
	stir->receiving = 1;

	stir->rx_buff.in_frame = FALSE;
	stir->rx_buff.state = OUTSIDE_FRAME;

	stir->rx_urb->status = 0;
	return usb_submit_urb(stir->rx_urb, GFP_KERNEL);
}