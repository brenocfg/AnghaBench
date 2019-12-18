#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/ * Lst_Member (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  Lst_Remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SuffUnRef(void *lp, void *sp)
{
    Lst l = (Lst) lp;

    LstNode ln = Lst_Member(l, sp);
    if (ln != NULL) {
	Lst_Remove(l, ln);
	((Suff *)sp)->refCount--;
    }
}