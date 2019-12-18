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
struct tty_struct {int dummy; } ;
struct TYPE_2__ {struct tty_struct* tty; } ;
struct specialix_port {int /*<<< orphan*/ * hits; TYPE_1__ port; } ;
struct specialix_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD186x_RDCR ; 
 int /*<<< orphan*/  CD186x_RDR ; 
 int /*<<< orphan*/  SX_DEBUG_RX ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct specialix_port* sx_get_port (struct specialix_board*,char*) ; 
 unsigned char sx_in (struct specialix_board*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_buffer_request_room (struct tty_struct*,unsigned char) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sx_receive(struct specialix_board *bp)
{
	struct specialix_port *port;
	struct tty_struct *tty;
	unsigned char count;

	func_enter();

	port = sx_get_port(bp, "Receive");
	if (port == NULL) {
		dprintk(SX_DEBUG_RX, "Hmm, couldn't find port.\n");
		func_exit();
		return;
	}
	tty = port->port.tty;

	count = sx_in(bp, CD186x_RDCR);
	dprintk(SX_DEBUG_RX, "port: %p: count: %d\n", port, count);
	port->hits[count > 8 ? 9 : count]++;

	tty_buffer_request_room(tty, count);

	while (count--)
		tty_insert_flip_char(tty, sx_in(bp, CD186x_RDR), TTY_NORMAL);
	tty_flip_buffer_push(tty);
	func_exit();
}