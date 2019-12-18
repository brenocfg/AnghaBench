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
struct sx_port {int dummy; } ;

/* Variables and functions */
 int OP_DTR ; 
 int OP_RTS ; 
 int /*<<< orphan*/  SX_DEBUG_MODEMSIGNALS ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  hi_op ; 
 int /*<<< orphan*/  sx_dprintk (int /*<<< orphan*/ ,char*,int,int) ; 
 int sx_read_channel_byte (struct sx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_write_channel_byte (struct sx_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sx_setsignals(struct sx_port *port, int dtr, int rts)
{
	int t;
	func_enter2();

	t = sx_read_channel_byte(port, hi_op);
	if (dtr >= 0)
		t = dtr ? (t | OP_DTR) : (t & ~OP_DTR);
	if (rts >= 0)
		t = rts ? (t | OP_RTS) : (t & ~OP_RTS);
	sx_write_channel_byte(port, hi_op, t);
	sx_dprintk(SX_DEBUG_MODEMSIGNALS, "setsignals: %d/%d\n", dtr, rts);

	func_exit();
}