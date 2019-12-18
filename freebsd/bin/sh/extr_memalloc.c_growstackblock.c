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
struct stack_block {struct stack_block* prev; } ;
typedef  int /*<<< orphan*/  pointer ;

/* Variables and functions */
 int ALIGN (int) ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int INT_MAX ; 
 char* SPACE (struct stack_block*) ; 
 struct stack_block* ckrealloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* sstrend ; 
 int stacknleft ; 
 char* stacknxt ; 
 struct stack_block* stackp ; 
 char* stalloc (int) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

__attribute__((used)) static void
growstackblock(int min)
{
	char *p;
	int newlen;
	char *oldspace;
	int oldlen;
	struct stack_block *sp;
	struct stack_block *oldstackp;

	if (min < stacknleft)
		min = stacknleft;
	if ((unsigned int)min >=
	    INT_MAX / 2 - ALIGN(sizeof(struct stack_block)))
		error("Out of space");
	min += stacknleft;
	min += ALIGN(sizeof(struct stack_block));
	newlen = 512;
	while (newlen < min)
		newlen <<= 1;
	oldspace = stacknxt;
	oldlen = stacknleft;

	if (stackp != NULL && stacknxt == SPACE(stackp)) {
		INTOFF;
		oldstackp = stackp;
		stackp = oldstackp->prev;
		sp = ckrealloc((pointer)oldstackp, newlen);
		sp->prev = stackp;
		stackp = sp;
		stacknxt = SPACE(sp);
		stacknleft = newlen - (stacknxt - (char*)sp);
		sstrend = stacknxt + stacknleft;
		INTON;
	} else {
		newlen -= ALIGN(sizeof(struct stack_block));
		p = stalloc(newlen);
		if (oldlen != 0)
			memcpy(p, oldspace, oldlen);
		stunalloc(p);
	}
}