#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* q_back; struct TYPE_7__* q_forw; } ;
struct TYPE_6__ {int type; TYPE_4__* t; TYPE_4__* h; } ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  REQUE (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
#define  UADD 131 
#define  UDEL 130 
#define  UMOV 129 
 int /*<<< orphan*/  USWAP (TYPE_1__,TYPE_1__) ; 
#define  VMOV 128 
 long addr_last ; 
 int /*<<< orphan*/  clear_active_list () ; 
 long current_addr ; 
 char* errmsg ; 
 int /*<<< orphan*/  get_addressed_line_node (int /*<<< orphan*/ ) ; 
 scalar_t__ isglobal ; 
 int modified ; 
 int u_addr_last ; 
 int u_current_addr ; 
 long u_p ; 
 TYPE_1__* ustack ; 

int
pop_undo_stack(void)
{
	long n;
	long o_current_addr = current_addr;
	long o_addr_last = addr_last;

	if (u_current_addr == -1 || u_addr_last == -1) {
		errmsg = "nothing to undo";
		return ERR;
	} else if (u_p)
		modified = 1;
	get_addressed_line_node(0);	/* this get_addressed_line_node last! */
	SPL1();
	for (n = u_p; n-- > 0;) {
		switch(ustack[n].type) {
		case UADD:
			REQUE(ustack[n].h->q_back, ustack[n].t->q_forw);
			break;
		case UDEL:
			REQUE(ustack[n].h->q_back, ustack[n].h);
			REQUE(ustack[n].t, ustack[n].t->q_forw);
			break;
		case UMOV:
		case VMOV:
			REQUE(ustack[n - 1].h, ustack[n].h->q_forw);
			REQUE(ustack[n].t->q_back, ustack[n - 1].t);
			REQUE(ustack[n].h, ustack[n].t);
			n--;
			break;
		default:
			/*NOTREACHED*/
			;
		}
		ustack[n].type ^= 1;
	}
	/* reverse undo stack order */
	for (n = u_p; n-- > (u_p + 1)/ 2;)
		USWAP(ustack[n], ustack[u_p - 1 - n]);
	if (isglobal)
		clear_active_list();
	current_addr = u_current_addr, u_current_addr = o_current_addr;
	addr_last = u_addr_last, u_addr_last = o_addr_last;
	SPL0();
	return 0;
}