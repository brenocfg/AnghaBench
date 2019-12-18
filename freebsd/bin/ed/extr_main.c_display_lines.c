#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; struct TYPE_4__* q_forw; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 int ERR ; 
 long INC_MOD (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_last ; 
 int /*<<< orphan*/  current_addr ; 
 char* errmsg ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 char* get_sbuf_line (TYPE_1__*) ; 
 scalar_t__ put_tty_line (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
display_lines(long from, long to, int gflag)
{
	line_t *bp;
	line_t *ep;
	char *s;

	if (!from) {
		errmsg = "invalid address";
		return ERR;
	}
	ep = get_addressed_line_node(INC_MOD(to, addr_last));
	bp = get_addressed_line_node(from);
	for (; bp != ep; bp = bp->q_forw) {
		if ((s = get_sbuf_line(bp)) == NULL)
			return ERR;
		if (put_tty_line(s, bp->len, current_addr = from++, gflag) < 0)
			return ERR;
	}
	return 0;
}