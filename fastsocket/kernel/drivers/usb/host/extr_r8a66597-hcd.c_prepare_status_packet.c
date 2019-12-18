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
struct urb {int* setup_packet; } ;
struct r8a66597_td {int /*<<< orphan*/  pipe; struct urb* urb; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int BCLR ; 
 int BEMP0 ; 
 int /*<<< orphan*/  BEMPSTS ; 
 int BVAL ; 
 int /*<<< orphan*/  CFIFOCTR ; 
 int /*<<< orphan*/  CFIFOSEL ; 
 int CURPIPE ; 
 int /*<<< orphan*/  DCPCFG ; 
 int ISEL ; 
 int /*<<< orphan*/  R8A66597_DIR ; 
 int USB_ENDPOINT_DIR_MASK ; 
 int /*<<< orphan*/  enable_irq_empty (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_nrdy (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_ready (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_start (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_stop (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_mdfy (struct r8a66597*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_pipe_toggle (struct r8a66597*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8a66597_reg_wait (struct r8a66597*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_status_packet(struct r8a66597 *r8a66597,
				  struct r8a66597_td *td)
{
	struct urb *urb = td->urb;

	r8a66597_pipe_toggle(r8a66597, td->pipe, 1);
	pipe_stop(r8a66597, td->pipe);

	if (urb->setup_packet[0] & USB_ENDPOINT_DIR_MASK) {
		r8a66597_bset(r8a66597, R8A66597_DIR, DCPCFG);
		r8a66597_mdfy(r8a66597, ISEL, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_wait(r8a66597, CFIFOSEL, CURPIPE, 0);
		r8a66597_write(r8a66597, ~BEMP0, BEMPSTS);
		r8a66597_write(r8a66597, BCLR | BVAL, CFIFOCTR);
		enable_irq_empty(r8a66597, 0);
	} else {
		r8a66597_bclr(r8a66597, R8A66597_DIR, DCPCFG);
		r8a66597_mdfy(r8a66597, 0, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_wait(r8a66597, CFIFOSEL, CURPIPE, 0);
		r8a66597_write(r8a66597, BCLR, CFIFOCTR);
		enable_irq_ready(r8a66597, 0);
	}
	enable_irq_nrdy(r8a66597, 0);
	pipe_start(r8a66597, td->pipe);
}