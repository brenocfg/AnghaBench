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
struct tty_struct {int /*<<< orphan*/  flags; TYPE_1__* termios; struct stliport* driver_data; } ;
struct tty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct stliport {size_t brdnr; int /*<<< orphan*/  state; int /*<<< orphan*/  asig; struct tty_port port; } ;
struct stlibrd {int dummy; } ;
typedef  int /*<<< orphan*/  asysigs_t ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  A_SETSIGNALSF ; 
 int HUPCL ; 
 int /*<<< orphan*/  ST_CLOSING ; 
 int /*<<< orphan*/  ST_CMDING ; 
 int /*<<< orphan*/  ST_DOFLUSHRX ; 
 int /*<<< orphan*/  ST_DOFLUSHTX ; 
 int /*<<< orphan*/  ST_DOSIGS ; 
 int /*<<< orphan*/  ST_RXSTOP ; 
 int /*<<< orphan*/  ST_TXBUSY ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct stlibrd** stli_brds ; 
 int /*<<< orphan*/  stli_lock ; 
 int /*<<< orphan*/  stli_mkasysigs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stli_nrbrds ; 
 int /*<<< orphan*/  stli_rawclose (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_sendcmd (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_hangup (struct tty_port*) ; 

__attribute__((used)) static void stli_hangup(struct tty_struct *tty)
{
	struct stliport *portp;
	struct stlibrd *brdp;
	struct tty_port *port;
	unsigned long flags;

	portp = tty->driver_data;
	if (portp == NULL)
		return;
	if (portp->brdnr >= stli_nrbrds)
		return;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return;
	port = &portp->port;

	spin_lock_irqsave(&port->lock, flags);
	port->flags &= ~ASYNC_INITIALIZED;
	spin_unlock_irqrestore(&port->lock, flags);

	if (!test_bit(ST_CLOSING, &portp->state))
		stli_rawclose(brdp, portp, 0, 0);

	spin_lock_irqsave(&stli_lock, flags);
	if (tty->termios->c_cflag & HUPCL) {
		stli_mkasysigs(&portp->asig, 0, 0);
		if (test_bit(ST_CMDING, &portp->state)) {
			set_bit(ST_DOSIGS, &portp->state);
			set_bit(ST_DOFLUSHTX, &portp->state);
			set_bit(ST_DOFLUSHRX, &portp->state);
		} else {
			stli_sendcmd(brdp, portp, A_SETSIGNALSF,
				&portp->asig, sizeof(asysigs_t), 0);
		}
	}

	clear_bit(ST_TXBUSY, &portp->state);
	clear_bit(ST_RXSTOP, &portp->state);
	set_bit(TTY_IO_ERROR, &tty->flags);
	spin_unlock_irqrestore(&stli_lock, flags);

	tty_port_hangup(port);
}