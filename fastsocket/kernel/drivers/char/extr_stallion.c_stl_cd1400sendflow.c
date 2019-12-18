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
struct TYPE_2__ {int /*<<< orphan*/  rxxoff; int /*<<< orphan*/  rxxon; } ;
struct stlport {int portnr; int /*<<< orphan*/  brdnr; TYPE_1__ stats; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR ; 
 int /*<<< orphan*/  CCR ; 
 int CCR_SENDSCHR1 ; 
 int CCR_SENDSCHR2 ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_cd1400ccrwait (struct stlport*) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stl_cd1400sendflow(struct stlport *portp, int state)
{
	struct tty_struct	*tty;
	unsigned long		flags;

	pr_debug("stl_cd1400sendflow(portp=%p,state=%x)\n", portp, state);

	if (portp == NULL)
		return;
	tty = tty_port_tty_get(&portp->port);
	if (tty == NULL)
		return;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));
	if (state) {
		stl_cd1400ccrwait(portp);
		stl_cd1400setreg(portp, CCR, CCR_SENDSCHR1);
		portp->stats.rxxon++;
		stl_cd1400ccrwait(portp);
	} else {
		stl_cd1400ccrwait(portp);
		stl_cd1400setreg(portp, CCR, CCR_SENDSCHR2);
		portp->stats.rxxoff++;
		stl_cd1400ccrwait(portp);
	}
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
	tty_kref_put(tty);
}