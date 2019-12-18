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
struct stlport {int /*<<< orphan*/  brdnr; scalar_t__ imr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stl_sc26198disableintrs(struct stlport *portp)
{
	unsigned long	flags;

	pr_debug("stl_sc26198disableintrs(portp=%p)\n", portp);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	portp->imr = 0;
	stl_sc26198setreg(portp, IMR, 0);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}