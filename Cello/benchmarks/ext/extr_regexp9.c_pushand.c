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
struct TYPE_3__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;
typedef  int /*<<< orphan*/  Reinst ;

/* Variables and functions */
 size_t NSTACK ; 
 TYPE_1__* andp ; 
 TYPE_1__* andstack ; 
 int /*<<< orphan*/  cant (char*) ; 

__attribute__((used)) static	void
pushand(Reinst *f, Reinst *l)
{
	if(andp >= &andstack[NSTACK])
		cant("operand stack overflow");
	andp->first = f;
	andp->last = l;
	andp++;
}