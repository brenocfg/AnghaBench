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
struct TYPE_2__ {int flags; int /*<<< orphan*/  open_wait; } ;
struct stlport {unsigned int sigs; TYPE_1__ port; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 unsigned int TIOCM_CD ; 
 unsigned int stl_getsignals (struct stlport*) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stl_cd_change(struct stlport *portp)
{
	unsigned int oldsigs = portp->sigs;
	struct tty_struct *tty = tty_port_tty_get(&portp->port);

	if (!tty)
		return;

	portp->sigs = stl_getsignals(portp);

	if ((portp->sigs & TIOCM_CD) && ((oldsigs & TIOCM_CD) == 0))
		wake_up_interruptible(&portp->port.open_wait);

	if ((oldsigs & TIOCM_CD) && ((portp->sigs & TIOCM_CD) == 0))
		if (portp->port.flags & ASYNC_CHECK_CD)
			tty_hangup(tty);
	tty_kref_put(tty);
}