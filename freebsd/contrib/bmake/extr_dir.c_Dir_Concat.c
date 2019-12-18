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
struct TYPE_4__ {int refCount; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * Lst_Succ (int /*<<< orphan*/ *) ; 

void
Dir_Concat(Lst path1, Lst path2)
{
    LstNode ln;
    Path    *p;

    for (ln = Lst_First(path2); ln != NULL; ln = Lst_Succ(ln)) {
	p = (Path *)Lst_Datum(ln);
	if (Lst_Member(path1, p) == NULL) {
	    p->refCount += 1;
	    (void)Lst_AtEnd(path1, p);
	}
    }
}