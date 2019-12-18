#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sorted; int /*<<< orphan*/  num_reserved; int /*<<< orphan*/  num_item; int /*<<< orphan*/  p; int /*<<< orphan*/  cmp; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_NUM (TYPE_1__*) ; 
 TYPE_1__* NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToArray (TYPE_1__*) ; 

LIST *CloneList(LIST *o)
{
	LIST *n = NewList(o->cmp);

	// Memory reallocation
	Free(n->p);
	n->p = ToArray(o);
	n->num_item = n->num_reserved = LIST_NUM(o);
	n->sorted = o->sorted;

	return n;
}