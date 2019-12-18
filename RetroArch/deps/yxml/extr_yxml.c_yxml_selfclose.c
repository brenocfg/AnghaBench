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
struct TYPE_4__ {int stacklen; char* elem; int /*<<< orphan*/  state; scalar_t__ stack; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  YXMLS_misc3 ; 
 int /*<<< orphan*/  YXML_ELEMEND ; 
 int /*<<< orphan*/  yxml_popstack (TYPE_1__*) ; 

__attribute__((used)) static yxml_ret_t yxml_selfclose(yxml_t *x, unsigned ch) {
	yxml_popstack(x);
	if(x->stacklen) {
		x->elem = (char *)x->stack+x->stacklen-1;
		while(*(x->elem-1))
			x->elem--;
		return YXML_ELEMEND;
	}
	x->elem = (char *)x->stack;
	x->state = YXMLS_misc3;
	return YXML_ELEMEND;
}