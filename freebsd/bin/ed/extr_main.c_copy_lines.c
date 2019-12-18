#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* t; } ;
typedef  TYPE_1__ undo_t ;
struct TYPE_9__ {struct TYPE_9__* q_forw; } ;
typedef  TYPE_2__ line_t ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 int /*<<< orphan*/  UADD ; 
 int /*<<< orphan*/  add_line_node (TYPE_2__*) ; 
 int current_addr ; 
 TYPE_2__* dup_line_node (TYPE_2__*) ; 
 int first_addr ; 
 TYPE_2__* get_addressed_line_node (int) ; 
 int modified ; 
 TYPE_1__* push_undo_stack (int /*<<< orphan*/ ,int,int) ; 
 int second_addr ; 

int
copy_lines(long addr)
{
	line_t *lp, *np = get_addressed_line_node(first_addr);
	undo_t *up = NULL;
	long n = second_addr - first_addr + 1;
	long m = 0;

	current_addr = addr;
	if (first_addr <= addr && addr < second_addr) {
		n =  addr - first_addr + 1;
		m = second_addr - addr;
	}
	for (; n > 0; n=m, m=0, np = get_addressed_line_node(current_addr + 1))
		for (; n-- > 0; np = np->q_forw) {
			SPL1();
			if ((lp = dup_line_node(np)) == NULL) {
				SPL0();
				return ERR;
			}
			add_line_node(lp);
			if (up)
				up->t = lp;
			else if ((up = push_undo_stack(UADD, current_addr,
			    current_addr)) == NULL) {
				SPL0();
				return ERR;
			}
			modified = 1;
			SPL0();
		}
	return 0;
}