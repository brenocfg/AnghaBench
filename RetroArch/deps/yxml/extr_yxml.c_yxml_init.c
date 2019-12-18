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
struct TYPE_4__ {int line; unsigned char* stack; size_t stacksize; char* elem; char* pi; char* attr; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ yxml_t ;

/* Variables and functions */
 int /*<<< orphan*/  YXMLS_init ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void yxml_init(yxml_t *x, void *stack, size_t stacksize) {
	memset(x, 0, sizeof(*x));
	x->line = 1;
	x->stack = (unsigned char *)stack;
	x->stacksize = stacksize;
	*x->stack = 0;
	x->elem = x->pi = x->attr = (char *)x->stack;
	x->state = YXMLS_init;
}