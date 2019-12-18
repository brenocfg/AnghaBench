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
struct TYPE_3__ {size_t stacklen; scalar_t__* stack; } ;
typedef  TYPE_1__ yxml_t ;

/* Variables and functions */

__attribute__((used)) static void yxml_popstack(yxml_t *x) {
	do
		x->stacklen--;
	while(x->stack[x->stacklen]);
}