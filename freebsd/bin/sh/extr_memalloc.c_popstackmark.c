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
struct stackmark {scalar_t__ stackp; scalar_t__ stacknleft; scalar_t__ stacknxt; } ;
struct stack_block {scalar_t__ prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  ckfree (struct stack_block*) ; 
 scalar_t__ sstrend ; 
 scalar_t__ stacknleft ; 
 scalar_t__ stacknxt ; 
 scalar_t__ stackp ; 

void
popstackmark(struct stackmark *mark)
{
	struct stack_block *sp;

	INTOFF;
	while (stackp != mark->stackp) {
		sp = stackp;
		stackp = sp->prev;
		ckfree(sp);
	}
	stacknxt = mark->stacknxt;
	stacknleft = mark->stacknleft;
	sstrend = stacknxt + stacknleft;
	INTON;
}