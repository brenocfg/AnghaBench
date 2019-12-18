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
struct r8a66597_td {size_t pipenum; TYPE_1__* urb; } ;
struct r8a66597 {int timeout_map; int /*<<< orphan*/ * td_timer; int /*<<< orphan*/ * pipe_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usb_pipecontrol (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_td_timer(struct r8a66597 *r8a66597, struct r8a66597_td *td)
{
	unsigned long time;

	BUG_ON(!td);

	if (!list_empty(&r8a66597->pipe_queue[td->pipenum]) &&
	    !usb_pipecontrol(td->urb->pipe) && usb_pipein(td->urb->pipe)) {
		r8a66597->timeout_map |= 1 << td->pipenum;
		switch (usb_pipetype(td->urb->pipe)) {
		case PIPE_INTERRUPT:
		case PIPE_ISOCHRONOUS:
			time = 30;
			break;
		default:
			time = 300;
			break;
		}

		mod_timer(&r8a66597->td_timer[td->pipenum],
			  jiffies + msecs_to_jiffies(time));
	}
}