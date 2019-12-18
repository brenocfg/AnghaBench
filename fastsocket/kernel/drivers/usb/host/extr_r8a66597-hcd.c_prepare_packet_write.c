#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct urb {scalar_t__ actual_length; int /*<<< orphan*/  pipe; } ;
struct r8a66597_td {int pipenum; TYPE_1__* pipe; struct urb* urb; } ;
struct r8a66597 {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fifoctr; scalar_t__ pipetre; } ;

/* Variables and functions */
 int BCLR ; 
 int /*<<< orphan*/  BRDYSTS ; 
 int /*<<< orphan*/  CFIFOCTR ; 
 int /*<<< orphan*/  CFIFOSEL ; 
 int CURPIPE ; 
 int /*<<< orphan*/  DCPCFG ; 
 int FRDY ; 
 int ISEL ; 
 int /*<<< orphan*/  R8A66597_DIR ; 
 int /*<<< orphan*/  TRENB ; 
 int /*<<< orphan*/  fifo_change_from_pipe (struct r8a66597*,TYPE_1__*) ; 
 int /*<<< orphan*/  packet_write (struct r8a66597*,int) ; 
 int /*<<< orphan*/  pipe_irq_enable (struct r8a66597*,struct urb*,int) ; 
 int /*<<< orphan*/  pipe_setting (struct r8a66597*,struct r8a66597_td*) ; 
 int /*<<< orphan*/  pipe_start (struct r8a66597*,TYPE_1__*) ; 
 int /*<<< orphan*/  pipe_stop (struct r8a66597*,TYPE_1__*) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_mdfy (struct r8a66597*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_pipe_toggle (struct r8a66597*,TYPE_1__*,int) ; 
 int r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_reg_wait (struct r8a66597*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usb_pipecontrol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_packet_write(struct r8a66597 *r8a66597,
				 struct r8a66597_td *td)
{
	u16 tmp;
	struct urb *urb = td->urb;

	if (usb_pipecontrol(urb->pipe)) {
		pipe_stop(r8a66597, td->pipe);
		r8a66597_bset(r8a66597, R8A66597_DIR, DCPCFG);
		r8a66597_mdfy(r8a66597, ISEL, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_wait(r8a66597, CFIFOSEL, CURPIPE, 0);
		if (urb->actual_length == 0) {
			r8a66597_pipe_toggle(r8a66597, td->pipe, 1);
			r8a66597_write(r8a66597, BCLR, CFIFOCTR);
		}
	} else {
		if (urb->actual_length == 0)
			pipe_setting(r8a66597, td);
		if (td->pipe->pipetre)
			r8a66597_bclr(r8a66597, TRENB, td->pipe->pipetre);
	}
	r8a66597_write(r8a66597, ~(1 << td->pipenum), BRDYSTS);

	fifo_change_from_pipe(r8a66597, td->pipe);
	tmp = r8a66597_read(r8a66597, td->pipe->fifoctr);
	if (unlikely((tmp & FRDY) == 0))
		pipe_irq_enable(r8a66597, urb, td->pipenum);
	else
		packet_write(r8a66597, td->pipenum);
	pipe_start(r8a66597, td->pipe);
}