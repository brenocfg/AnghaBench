#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ undo_t ;

/* Variables and functions */
 int EOF ; 
 int ERR ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 int /*<<< orphan*/  UADD ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 long current_addr ; 
 int /*<<< orphan*/  get_addressed_line_node (long) ; 
 int get_tty_line () ; 
 char* ibuf ; 
 char const* ibufp ; 
 int /*<<< orphan*/  isglobal ; 
 int modified ; 
 TYPE_1__* push_undo_stack (int /*<<< orphan*/ ,long,long) ; 
 char* put_sbuf_line (char const*) ; 
 int /*<<< orphan*/  stdin ; 

int
append_lines(long n)
{
	int l;
	const char *lp = ibuf;
	const char *eot;
	undo_t *up = NULL;

	for (current_addr = n;;) {
		if (!isglobal) {
			if ((l = get_tty_line()) < 0)
				return ERR;
			else if (l == 0 || ibuf[l - 1] != '\n') {
				clearerr(stdin);
				return  l ? EOF : 0;
			}
			lp = ibuf;
		} else if (*(lp = ibufp) == '\0')
			return 0;
		else {
			while (*ibufp++ != '\n')
				;
			l = ibufp - lp;
		}
		if (l == 2 && lp[0] == '.' && lp[1] == '\n') {
			return 0;
		}
		eot = lp + l;
		SPL1();
		do {
			if ((lp = put_sbuf_line(lp)) == NULL) {
				SPL0();
				return ERR;
			} else if (up)
				up->t = get_addressed_line_node(current_addr);
			else if ((up = push_undo_stack(UADD, current_addr,
			    current_addr)) == NULL) {
				SPL0();
				return ERR;
			}
		} while (lp != eot);
		modified = 1;
		SPL0();
	}
	/* NOTREACHED */
}