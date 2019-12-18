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
struct tty_struct {int flags; struct stliport* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sigvalue; } ;
struct stliport {size_t brdnr; TYPE_1__ asig; } ;
struct stlibrd {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  asysigs_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETSIGNALS ; 
 int EIO ; 
 int ENODEV ; 
 int TTY_IO_ERROR ; 
 struct stlibrd** stli_brds ; 
 int stli_cmdwait (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int stli_mktiocm (int /*<<< orphan*/ ) ; 
 size_t stli_nrbrds ; 

__attribute__((used)) static int stli_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct stliport *portp = tty->driver_data;
	struct stlibrd *brdp;
	int rc;

	if (portp == NULL)
		return -ENODEV;
	if (portp->brdnr >= stli_nrbrds)
		return 0;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return 0;
	if (tty->flags & (1 << TTY_IO_ERROR))
		return -EIO;

	if ((rc = stli_cmdwait(brdp, portp, A_GETSIGNALS,
			       &portp->asig, sizeof(asysigs_t), 1)) < 0)
		return rc;

	return stli_mktiocm(portp->asig.sigvalue);
}