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
struct putchar_args {int flags; int /*<<< orphan*/ * tty; } ;

/* Variables and functions */
 int TOCONS ; 
 int TOLOG ; 
 int TOLOGLOCKED ; 
 int TOSTR ; 
 int TOTTY ; 
 int /*<<< orphan*/ * constty ; 
 scalar_t__ debugger_panic_str ; 
 int /*<<< orphan*/  log_putc (int) ; 
 int /*<<< orphan*/  log_putc_locked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msgbufp ; 
 int /*<<< orphan*/  stub1 (int) ; 
 scalar_t__ tputchar (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_putc (int) ; 

void
putchar(int c, void *arg)
{
	struct putchar_args *pca = arg;
	char **sp = (char**) pca->tty;

	if (debugger_panic_str)
		constty = 0;
	if ((pca->flags & TOCONS) && pca->tty == NULL && constty) {
		pca->tty = constty;
		pca->flags |= TOTTY;
	}
	if ((pca->flags & TOTTY) && pca->tty && tputchar(c, pca->tty) < 0 &&
	    (pca->flags & TOCONS) && pca->tty == constty)
		constty = 0;
	if ((pca->flags & TOLOG) && c != '\0' && c != '\r' && c != 0177)
		log_putc(c);
	if ((pca->flags & TOLOGLOCKED) && c != '\0' && c != '\r' && c != 0177)
		log_putc_locked(msgbufp, c);
	if ((pca->flags & TOCONS) && constty == 0 && c != '\0')
		(*v_putc)(c);
	if (pca->flags & TOSTR) {
		**sp = c;
		(*sp)++;
	}
}