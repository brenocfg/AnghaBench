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
struct tty_struct {struct stliport* driver_data; } ;
struct stliport {size_t brdnr; } ;
struct stlibrd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BREAK ; 
 long BREAKOFF ; 
 long BREAKON ; 
 int EINVAL ; 
 struct stlibrd** stli_brds ; 
 int /*<<< orphan*/  stli_cmdwait (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,long*,int,int /*<<< orphan*/ ) ; 
 size_t stli_nrbrds ; 

__attribute__((used)) static int stli_breakctl(struct tty_struct *tty, int state)
{
	struct stlibrd	*brdp;
	struct stliport	*portp;
	long		arg;

	portp = tty->driver_data;
	if (portp == NULL)
		return -EINVAL;
	if (portp->brdnr >= stli_nrbrds)
		return -EINVAL;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return -EINVAL;

	arg = (state == -1) ? BREAKON : BREAKOFF;
	stli_cmdwait(brdp, portp, A_BREAK, &arg, sizeof(long), 0);
	return 0;
}