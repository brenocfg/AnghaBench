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
typedef  int /*<<< orphan*/  u32 ;
struct tty_struct {struct stliport* driver_data; } ;
struct stliport {size_t brdnr; int /*<<< orphan*/  state; } ;
struct stlibrd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FLUSH ; 
 unsigned long FLUSHRX ; 
 unsigned long FLUSHTX ; 
 int /*<<< orphan*/  ST_CMDING ; 
 int /*<<< orphan*/  ST_DOFLUSHRX ; 
 int /*<<< orphan*/  ST_DOFLUSHTX ; 
 int /*<<< orphan*/  __stli_sendcmd (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct stlibrd** stli_brds ; 
 size_t stli_nrbrds ; 
 scalar_t__ stli_txcookrealsize ; 
 scalar_t__ stli_txcooksize ; 
 struct tty_struct* stli_txcooktty ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void stli_flushbuffer(struct tty_struct *tty)
{
	struct stliport *portp;
	struct stlibrd *brdp;
	unsigned long ftype, flags;

	portp = tty->driver_data;
	if (portp == NULL)
		return;
	if (portp->brdnr >= stli_nrbrds)
		return;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return;

	spin_lock_irqsave(&brd_lock, flags);
	if (tty == stli_txcooktty) {
		stli_txcooktty = NULL;
		stli_txcooksize = 0;
		stli_txcookrealsize = 0;
	}
	if (test_bit(ST_CMDING, &portp->state)) {
		set_bit(ST_DOFLUSHTX, &portp->state);
	} else {
		ftype = FLUSHTX;
		if (test_bit(ST_DOFLUSHRX, &portp->state)) {
			ftype |= FLUSHRX;
			clear_bit(ST_DOFLUSHRX, &portp->state);
		}
		__stli_sendcmd(brdp, portp, A_FLUSH, &ftype, sizeof(u32), 0);
	}
	spin_unlock_irqrestore(&brd_lock, flags);
	tty_wakeup(tty);
}