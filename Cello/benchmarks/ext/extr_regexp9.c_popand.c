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
typedef  int /*<<< orphan*/  Reinst ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  NOP ; 
 int /*<<< orphan*/ * andp ; 
 int /*<<< orphan*/ * andstack ; 
 int /*<<< orphan*/ * newinst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushand (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regerr2 (char*,int) ; 

__attribute__((used)) static	Node*
popand(int op)
{
	Reinst *inst;

	if(andp <= &andstack[0]){
		regerr2("missing operand for ", op);
		inst = newinst(NOP);
		pushand(inst,inst);
	}
	return --andp;
}