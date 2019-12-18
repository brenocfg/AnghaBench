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
struct tty_struct {int /*<<< orphan*/  termios; struct stliport* driver_data; } ;
struct stliport {size_t brdnr; } ;
struct stlibrd {int dummy; } ;
typedef  int /*<<< orphan*/  asyport_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SETPORT ; 
 int ENODEV ; 
 struct stlibrd** stli_brds ; 
 int stli_cmdwait (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_mkasyport (struct tty_struct*,struct stliport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t stli_nrbrds ; 

__attribute__((used)) static int stli_setport(struct tty_struct *tty)
{
	struct stliport *portp = tty->driver_data;
	struct stlibrd *brdp;
	asyport_t aport;

	if (portp == NULL)
		return -ENODEV;
	if (portp->brdnr >= stli_nrbrds)
		return -ENODEV;
	brdp = stli_brds[portp->brdnr];
	if (brdp == NULL)
		return -ENODEV;

	stli_mkasyport(tty, portp, &aport, tty->termios);
	return(stli_cmdwait(brdp, portp, A_SETPORT, &aport, sizeof(asyport_t), 0));
}