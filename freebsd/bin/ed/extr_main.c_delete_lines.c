#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  q_forw; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 int ERR ; 
 long INC_MOD (long,long) ; 
 int /*<<< orphan*/  REQUE (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 int /*<<< orphan*/  UDEL ; 
 long addr_last ; 
 long current_addr ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 scalar_t__ isglobal ; 
 int modified ; 
 int /*<<< orphan*/ * push_undo_stack (int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  unset_active_nodes (int /*<<< orphan*/ ,TYPE_1__*) ; 

int
delete_lines(long from, long to)
{
	line_t *n, *p;

	SPL1();
	if (push_undo_stack(UDEL, from, to) == NULL) {
		SPL0();
		return ERR;
	}
	n = get_addressed_line_node(INC_MOD(to, addr_last));
	p = get_addressed_line_node(from - 1);
					/* this get_addressed_line_node last! */
	if (isglobal)
		unset_active_nodes(p->q_forw, n);
	REQUE(p, n);
	addr_last -= to - from + 1;
	current_addr = from - 1;
	modified = 1;
	SPL0();
	return 0;
}