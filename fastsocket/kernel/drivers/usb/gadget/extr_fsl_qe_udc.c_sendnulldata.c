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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct qe_udc {scalar_t__ nullbuf; } ;
struct qe_frame {int dummy; } ;
struct qe_ep {struct qe_udc* udc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FRAME_OK ; 
 int NO_CRC ; 
 int ZLP ; 
 int /*<<< orphan*/  frame_set_data (struct qe_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_set_info (struct qe_frame*,int) ; 
 int /*<<< orphan*/  frame_set_length (struct qe_frame*,int) ; 
 int /*<<< orphan*/  frame_set_status (struct qe_frame*,int /*<<< orphan*/ ) ; 
 int qe_ep_tx (struct qe_ep*,struct qe_frame*) ; 
 int /*<<< orphan*/  qe_frame_clean (struct qe_frame*) ; 

__attribute__((used)) static int sendnulldata(struct qe_ep *ep, struct qe_frame *frame, uint infor)
{
	struct qe_udc *udc = ep->udc;

	if (frame == NULL)
		return -ENODEV;

	qe_frame_clean(frame);
	frame_set_data(frame, (u8 *)udc->nullbuf);
	frame_set_length(frame, 2);
	frame_set_status(frame, FRAME_OK);
	frame_set_info(frame, (ZLP | NO_CRC | infor));

	return qe_ep_tx(ep, frame);
}