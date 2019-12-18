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
struct tty_struct {int flags; struct stliport* driver_data; } ;
struct stliport {size_t brdnr; int /*<<< orphan*/  asig; } ;
struct stlibrd {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  asysigs_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SETSIGNALS ; 
 int EIO ; 
 int ENODEV ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int TTY_IO_ERROR ; 
 struct stlibrd** stli_brds ; 
 int stli_cmdwait (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_mkasysigs (int /*<<< orphan*/ *,int,int) ; 
 size_t stli_nrbrds ; 

__attribute__((used)) static int stli_tiocmset(struct tty_struct *tty, struct file *file,
			 unsigned int set, unsigned int clear)
{
	struct stliport *portp = tty->driver_data;
	struct stlibrd *brdp;
	int rts = -1, dtr = -1;

	if (portp == NULL)
		return -ENODEV;
	if (portp->brdnr >= stli_nrbrds)
		return 0;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return 0;
	if (tty->flags & (1 << TTY_IO_ERROR))
		return -EIO;

	if (set & TIOCM_RTS)
		rts = 1;
	if (set & TIOCM_DTR)
		dtr = 1;
	if (clear & TIOCM_RTS)
		rts = 0;
	if (clear & TIOCM_DTR)
		dtr = 0;

	stli_mkasysigs(&portp->asig, dtr, rts);

	return stli_cmdwait(brdp, portp, A_SETSIGNALS, &portp->asig,
			    sizeof(asysigs_t), 0);
}