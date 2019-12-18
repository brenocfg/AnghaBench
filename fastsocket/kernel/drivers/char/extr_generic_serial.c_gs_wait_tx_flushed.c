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
struct TYPE_2__ {int /*<<< orphan*/  tty; } ;
struct gs_port {int baud; TYPE_1__ port; int /*<<< orphan*/  xmit_buf; int /*<<< orphan*/  xmit_cnt; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GS_DEBUG_FLUSH ; 
 int HZ ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  gs_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int gs_real_chars_in_buffer (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int gs_wait_tx_flushed (void * ptr, unsigned long timeout) 
{
	struct gs_port *port = ptr;
	unsigned long end_jiffies;
	int jiffies_to_transmit, charsleft = 0, rv = 0;
	int rcib;

	func_enter();

	gs_dprintk (GS_DEBUG_FLUSH, "port=%p.\n", port);
	if (port) {
		gs_dprintk (GS_DEBUG_FLUSH, "xmit_cnt=%x, xmit_buf=%p, tty=%p.\n", 
		port->xmit_cnt, port->xmit_buf, port->port.tty);
	}

	if (!port || port->xmit_cnt < 0 || !port->xmit_buf) {
		gs_dprintk (GS_DEBUG_FLUSH, "ERROR: !port, !port->xmit_buf or prot->xmit_cnt < 0.\n");
		func_exit();
		return -EINVAL;  /* This is an error which we don't know how to handle. */
	}

	rcib = gs_real_chars_in_buffer(port->port.tty);

	if(rcib <= 0) {
		gs_dprintk (GS_DEBUG_FLUSH, "nothing to wait for.\n");
		func_exit();
		return rv;
	}
	/* stop trying: now + twice the time it would normally take +  seconds */
	if (timeout == 0) timeout = MAX_SCHEDULE_TIMEOUT;
	end_jiffies  = jiffies; 
	if (timeout !=  MAX_SCHEDULE_TIMEOUT)
		end_jiffies += port->baud?(2 * rcib * 10 * HZ / port->baud):0;
	end_jiffies += timeout;

	gs_dprintk (GS_DEBUG_FLUSH, "now=%lx, end=%lx (%ld).\n", 
		    jiffies, end_jiffies, end_jiffies-jiffies); 

	/* the expression is actually jiffies < end_jiffies, but that won't
	   work around the wraparound. Tricky eh? */
	while ((charsleft = gs_real_chars_in_buffer (port->port.tty)) &&
	        time_after (end_jiffies, jiffies)) {
		/* Units check: 
		   chars * (bits/char) * (jiffies /sec) / (bits/sec) = jiffies!
		   check! */

		charsleft += 16; /* Allow 16 chars more to be transmitted ... */
		jiffies_to_transmit = port->baud?(1 + charsleft * 10 * HZ / port->baud):0;
		/*                                ^^^ Round up.... */
		if (jiffies_to_transmit <= 0) jiffies_to_transmit = 1;

		gs_dprintk (GS_DEBUG_FLUSH, "Expect to finish in %d jiffies "
			    "(%d chars).\n", jiffies_to_transmit, charsleft); 

		msleep_interruptible(jiffies_to_msecs(jiffies_to_transmit));
		if (signal_pending (current)) {
			gs_dprintk (GS_DEBUG_FLUSH, "Signal pending. Bombing out: "); 
			rv = -EINTR;
			break;
		}
	}

	gs_dprintk (GS_DEBUG_FLUSH, "charsleft = %d.\n", charsleft); 
	set_current_state (TASK_RUNNING);

	func_exit();
	return rv;
}