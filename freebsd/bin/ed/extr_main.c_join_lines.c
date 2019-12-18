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
struct TYPE_4__ {int len; struct TYPE_4__* q_forw; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 int ERR ; 
 long INC_MOD (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REALLOC (char*,int,int,int) ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 int /*<<< orphan*/  UADD ; 
 int /*<<< orphan*/  addr_last ; 
 long current_addr ; 
 scalar_t__ delete_lines (long,long) ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 char* get_sbuf_line (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int modified ; 
 int /*<<< orphan*/ * push_undo_stack (int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/ * put_sbuf_line (char*) ; 

int
join_lines(long from, long to)
{
	static char *buf = NULL;
	static int n;

	char *s;
	int size = 0;
	line_t *bp, *ep;

	ep = get_addressed_line_node(INC_MOD(to, addr_last));
	bp = get_addressed_line_node(from);
	for (; bp != ep; bp = bp->q_forw) {
		if ((s = get_sbuf_line(bp)) == NULL)
			return ERR;
		REALLOC(buf, n, size + bp->len, ERR);
		memcpy(buf + size, s, bp->len);
		size += bp->len;
	}
	REALLOC(buf, n, size + 2, ERR);
	memcpy(buf + size, "\n", 2);
	if (delete_lines(from, to) < 0)
		return ERR;
	current_addr = from - 1;
	SPL1();
	if (put_sbuf_line(buf) == NULL ||
	    push_undo_stack(UADD, current_addr, current_addr) == NULL) {
		SPL0();
		return ERR;
	}
	modified = 1;
	SPL0();
	return 0;
}