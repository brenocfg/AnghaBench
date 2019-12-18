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
struct urb {int number_of_packets; TYPE_1__* iso_frame_desc; int /*<<< orphan*/  error_count; struct c67x00_urb_priv* hcpriv; } ;
struct c67x00_urb_priv {int dummy; } ;
struct c67x00_td {int privdata; int status; struct urb* urb; } ;
struct c67x00_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; } ;

/* Variables and functions */
 int TD_ERROR_MASK ; 
 int /*<<< orphan*/  c67x00_giveback_urb (struct c67x00_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c67x00_td_to_error (struct c67x00_hcd*,struct c67x00_td*) ; 
 int /*<<< orphan*/  td_actual_bytes (struct c67x00_td*) ; 

__attribute__((used)) static void c67x00_handle_isoc(struct c67x00_hcd *c67x00, struct c67x00_td *td)
{
	struct urb *urb = td->urb;
	struct c67x00_urb_priv *urbp;
	int cnt;

	if (!urb)
		return;

	urbp = urb->hcpriv;
	cnt = td->privdata;

	if (td->status & TD_ERROR_MASK)
		urb->error_count++;

	urb->iso_frame_desc[cnt].actual_length = td_actual_bytes(td);
	urb->iso_frame_desc[cnt].status = c67x00_td_to_error(c67x00, td);
	if (cnt + 1 == urb->number_of_packets)	/* Last packet */
		c67x00_giveback_urb(c67x00, urb, 0);
}