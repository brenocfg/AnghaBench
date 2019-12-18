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
struct urb {int /*<<< orphan*/  interval; struct c67x00_urb_priv* hcpriv; } ;
struct c67x00_urb_priv {TYPE_1__* ep_data; } ;
struct c67x00_hcd {int /*<<< orphan*/  current_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_frame; } ;

/* Variables and functions */
 int c67x00_add_data_urb (struct c67x00_hcd*,struct urb*) ; 
 int /*<<< orphan*/  frame_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c67x00_add_int_urb(struct c67x00_hcd *c67x00, struct urb *urb)
{
	struct c67x00_urb_priv *urbp = urb->hcpriv;

	if (frame_after_eq(c67x00->current_frame, urbp->ep_data->next_frame)) {
		urbp->ep_data->next_frame =
		    frame_add(urbp->ep_data->next_frame, urb->interval);
		return c67x00_add_data_urb(c67x00, urb);
	}
	return 0;
}