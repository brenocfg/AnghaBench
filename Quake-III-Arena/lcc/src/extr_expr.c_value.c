#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
struct TYPE_9__ {int /*<<< orphan*/  op; } ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 int AND ; 
 int EQ ; 
 int GE ; 
 int GT ; 
 int LE ; 
 int LT ; 
 int NE ; 
 int NOT ; 
 int OR ; 
 TYPE_1__* condtree (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consttree (int,int /*<<< orphan*/ ) ; 
 int generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 TYPE_4__* rightkid (TYPE_1__*) ; 
 scalar_t__ voidtype ; 

Tree value(Tree p) {
	int op = generic(rightkid(p)->op);

	if (p->type != voidtype
	&& (op==AND || op==OR || op==NOT || op==EQ || op==NE
	||  op== LE || op==LT || op== GE || op==GT))
		p = condtree(p, consttree(1, inttype),
			consttree(0, inttype));
	return p;
}