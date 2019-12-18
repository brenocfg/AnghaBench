#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_6__ {struct tty_struct* tty; } ;
struct TYPE_7__ {long closing_wait; TYPE_1__ port; } ;
struct Port {int State; scalar_t__ InUse; scalar_t__ TxBufferIn; scalar_t__ TxBufferOut; int PortState; int Config; int /*<<< orphan*/  portSem; scalar_t__ firstOpen; int /*<<< orphan*/  closes; scalar_t__ statsGather; int /*<<< orphan*/  PortNum; int /*<<< orphan*/  ModemState; TYPE_2__ gs; } ;
struct TYPE_8__ {scalar_t__ RIOHalted; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int HUNDRED_MS ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ NOT_INUSE ; 
 int PORT_ISOPEN ; 
 int /*<<< orphan*/  RIOC_CLOSE ; 
 int /*<<< orphan*/  RIOC_FCLOSE ; 
 int /*<<< orphan*/  RIOC_MSVR1_CD ; 
 int /*<<< orphan*/  RIOClearUp (struct Port*) ; 
 scalar_t__ RIODelay (struct Port*,int) ; 
 scalar_t__ RIODelay_ni (struct Port*,int) ; 
 int /*<<< orphan*/  RIOPreemptiveCmd (TYPE_3__*,struct Port*,int /*<<< orphan*/ ) ; 
 scalar_t__ RIOShortCommand (TYPE_3__*,struct Port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int RIO_CARR_ON ; 
 int RIO_CLOSING ; 
 int RIO_CTSFLOW ; 
 int /*<<< orphan*/  RIO_DEBUG_TTY ; 
 int RIO_DELETED ; 
 int RIO_DYNOROD ; 
 scalar_t__ RIO_FAIL ; 
 int RIO_LOPEN ; 
 int RIO_MOPEN ; 
 int RIO_RTSFLOW ; 
 unsigned long jiffies ; 
 TYPE_3__* p ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int riotclose(void *ptr)
{
	struct Port *PortP = ptr;	/* pointer to the port structure */
	int deleted = 0;
	int try = -1;		/* Disable the timeouts by setting them to -1 */
	int repeat_this = -1;	/* Congrats to those having 15 years of
				   uptime! (You get to break the driver.) */
	unsigned long end_time;
	struct tty_struct *tty;
	unsigned long flags;
	int rv = 0;

	rio_dprintk(RIO_DEBUG_TTY, "port close SysPort %d\n", PortP->PortNum);

	/* PortP = p->RIOPortp[SysPort]; */
	rio_dprintk(RIO_DEBUG_TTY, "Port is at address %p\n", PortP);
	/* tp = PortP->TtyP; *//* Get tty */
	tty = PortP->gs.port.tty;
	rio_dprintk(RIO_DEBUG_TTY, "TTY is at address %p\n", tty);

	if (PortP->gs.closing_wait)
		end_time = jiffies + PortP->gs.closing_wait;
	else
		end_time = jiffies + MAX_SCHEDULE_TIMEOUT;

	rio_spin_lock_irqsave(&PortP->portSem, flags);

	/*
	 ** Setting this flag will make any process trying to open
	 ** this port block until we are complete closing it.
	 */
	PortP->State |= RIO_CLOSING;

	if ((PortP->State & RIO_DELETED)) {
		rio_dprintk(RIO_DEBUG_TTY, "Close on deleted RTA\n");
		deleted = 1;
	}

	if (p->RIOHalted) {
		RIOClearUp(PortP);
		rv = -EIO;
		goto close_end;
	}

	rio_dprintk(RIO_DEBUG_TTY, "Clear bits\n");
	/*
	 ** clear the open bits for this device
	 */
	PortP->State &= ~RIO_MOPEN;
	PortP->State &= ~RIO_CARR_ON;
	PortP->ModemState &= ~RIOC_MSVR1_CD;
	/*
	 ** If the device was open as both a Modem and a tty line
	 ** then we need to wimp out here, as the port has not really
	 ** been finally closed (gee, whizz!) The test here uses the
	 ** bit for the OTHER mode of operation, to see if THAT is
	 ** still active!
	 */
	if ((PortP->State & (RIO_LOPEN | RIO_MOPEN))) {
		/*
		 ** The port is still open for the other task -
		 ** return, pretending that we are still active.
		 */
		rio_dprintk(RIO_DEBUG_TTY, "Channel %d still open !\n", PortP->PortNum);
		PortP->State &= ~RIO_CLOSING;
		if (PortP->firstOpen)
			PortP->firstOpen--;
		rio_spin_unlock_irqrestore(&PortP->portSem, flags);
		return -EIO;
	}

	rio_dprintk(RIO_DEBUG_TTY, "Closing down - everything must go!\n");

	PortP->State &= ~RIO_DYNOROD;

	/*
	 ** This is where we wait for the port
	 ** to drain down before closing. Bye-bye....
	 ** (We never meant to do this)
	 */
	rio_dprintk(RIO_DEBUG_TTY, "Timeout 1 starts\n");

	if (!deleted)
		while ((PortP->InUse != NOT_INUSE) && !p->RIOHalted && (PortP->TxBufferIn != PortP->TxBufferOut)) {
			if (repeat_this-- <= 0) {
				rv = -EINTR;
				rio_dprintk(RIO_DEBUG_TTY, "Waiting for not idle closed broken by signal\n");
				RIOPreemptiveCmd(p, PortP, RIOC_FCLOSE);
				goto close_end;
			}
			rio_dprintk(RIO_DEBUG_TTY, "Calling timeout to flush in closing\n");
			rio_spin_unlock_irqrestore(&PortP->portSem, flags);
			if (RIODelay_ni(PortP, HUNDRED_MS * 10) == RIO_FAIL) {
				rio_dprintk(RIO_DEBUG_TTY, "RTA EINTR in delay \n");
				rv = -EINTR;
				rio_spin_lock_irqsave(&PortP->portSem, flags);
				goto close_end;
			}
			rio_spin_lock_irqsave(&PortP->portSem, flags);
		}

	PortP->TxBufferIn = PortP->TxBufferOut = 0;
	repeat_this = 0xff;

	PortP->InUse = 0;
	if ((PortP->State & (RIO_LOPEN | RIO_MOPEN))) {
		/*
		 ** The port has been re-opened for the other task -
		 ** return, pretending that we are still active.
		 */
		rio_dprintk(RIO_DEBUG_TTY, "Channel %d re-open!\n", PortP->PortNum);
		PortP->State &= ~RIO_CLOSING;
		rio_spin_unlock_irqrestore(&PortP->portSem, flags);
		if (PortP->firstOpen)
			PortP->firstOpen--;
		return -EIO;
	}

	if (p->RIOHalted) {
		RIOClearUp(PortP);
		goto close_end;
	}

	/* Can't call RIOShortCommand with the port locked. */
	rio_spin_unlock_irqrestore(&PortP->portSem, flags);

	if (RIOShortCommand(p, PortP, RIOC_CLOSE, 1, 0) == RIO_FAIL) {
		RIOPreemptiveCmd(p, PortP, RIOC_FCLOSE);
		rio_spin_lock_irqsave(&PortP->portSem, flags);
		goto close_end;
	}

	if (!deleted)
		while (try && (PortP->PortState & PORT_ISOPEN)) {
			try--;
			if (time_after(jiffies, end_time)) {
				rio_dprintk(RIO_DEBUG_TTY, "Run out of tries - force the bugger shut!\n");
				RIOPreemptiveCmd(p, PortP, RIOC_FCLOSE);
				break;
			}
			rio_dprintk(RIO_DEBUG_TTY, "Close: PortState:ISOPEN is %d\n", PortP->PortState & PORT_ISOPEN);

			if (p->RIOHalted) {
				RIOClearUp(PortP);
				rio_spin_lock_irqsave(&PortP->portSem, flags);
				goto close_end;
			}
			if (RIODelay(PortP, HUNDRED_MS) == RIO_FAIL) {
				rio_dprintk(RIO_DEBUG_TTY, "RTA EINTR in delay \n");
				RIOPreemptiveCmd(p, PortP, RIOC_FCLOSE);
				break;
			}
		}
	rio_spin_lock_irqsave(&PortP->portSem, flags);
	rio_dprintk(RIO_DEBUG_TTY, "Close: try was %d on completion\n", try);

	/* RIOPreemptiveCmd(p, PortP, RIOC_FCLOSE); */

/*
** 15.10.1998 ARG - ESIL 0761 part fix
** RIO has it's own CTSFLOW and RTSFLOW flags in 'Config' in the port structure,** we need to make sure that the flags are clear when the port is opened.
*/
	PortP->Config &= ~(RIO_CTSFLOW | RIO_RTSFLOW);

	/*
	 ** Count opens for port statistics reporting
	 */
	if (PortP->statsGather)
		PortP->closes++;

close_end:
	/* XXX: Why would a "DELETED" flag be reset here? I'd have
	   thought that a "deleted" flag means that the port was
	   permanently gone, but here we can make it reappear by it
	   being in close during the "deletion".
	 */
	PortP->State &= ~(RIO_CLOSING | RIO_DELETED);
	if (PortP->firstOpen)
		PortP->firstOpen--;
	rio_spin_unlock_irqrestore(&PortP->portSem, flags);
	rio_dprintk(RIO_DEBUG_TTY, "Return from close\n");
	return rv;
}