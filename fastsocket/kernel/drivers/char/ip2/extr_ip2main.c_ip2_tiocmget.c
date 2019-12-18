#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct tty_struct {size_t index; } ;
struct file {int dummy; } ;
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_4__ {int dataSetOut; int dataSetIn; int /*<<< orphan*/  dss_now_wait; int /*<<< orphan*/  pMyBord; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DSS_NOW ; 
 TYPE_1__** DevTable ; 
 int EINTR ; 
 int ENODEV ; 
 int I2_CTS ; 
 int I2_DCD ; 
 int I2_DSR ; 
 int I2_DTR ; 
 int I2_RI ; 
 int I2_RTS ; 
 int /*<<< orphan*/  PTYPE_BYPASS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int TIOCM_CAR ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RNG ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  i2QueueCommands (int /*<<< orphan*/ ,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  serviceOutgoingFifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip2_tiocmget(struct tty_struct *tty, struct file *file)
{
	i2ChanStrPtr pCh = DevTable[tty->index];
#ifdef	ENABLE_DSSNOW
	wait_queue_t wait;
#endif

	if (pCh == NULL)
		return -ENODEV;

/*
	FIXME - the following code is causing a NULL pointer dereference in
	2.3.51 in an interrupt handler.  It's suppose to prompt the board
	to return the DSS signal status immediately.  Why doesn't it do
	the same thing in 2.2.14?
*/

/*	This thing is still busted in the 1.2.12 driver on 2.4.x
	and even hoses the serial console so the oops can be trapped.
		/\/\|=mhw=|\/\/			*/

#ifdef	ENABLE_DSSNOW
	i2QueueCommands(PTYPE_BYPASS, pCh, 100, 1, CMD_DSS_NOW);

	init_waitqueue_entry(&wait, current);
	add_wait_queue(&pCh->dss_now_wait, &wait);
	set_current_state( TASK_INTERRUPTIBLE );

	serviceOutgoingFifo( pCh->pMyBord );

	schedule();

	set_current_state( TASK_RUNNING );
	remove_wait_queue(&pCh->dss_now_wait, &wait);

	if (signal_pending(current)) {
		return -EINTR;
	}
#endif
	return  ((pCh->dataSetOut & I2_RTS) ? TIOCM_RTS : 0)
	      | ((pCh->dataSetOut & I2_DTR) ? TIOCM_DTR : 0)
	      | ((pCh->dataSetIn  & I2_DCD) ? TIOCM_CAR : 0)
	      | ((pCh->dataSetIn  & I2_RI)  ? TIOCM_RNG : 0)
	      | ((pCh->dataSetIn  & I2_DSR) ? TIOCM_DSR : 0)
	      | ((pCh->dataSetIn  & I2_CTS) ? TIOCM_CTS : 0);
}