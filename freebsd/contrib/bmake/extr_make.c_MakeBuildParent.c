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
struct TYPE_3__ {scalar_t__ made; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEFERRED ; 
 int /*<<< orphan*/  DONE_ORDER ; 
 scalar_t__ MakeBuildChild (TYPE_1__*,void*) ; 

__attribute__((used)) static int
MakeBuildParent(void *v_pn, void *toBeMade_next)
{
    GNode *pn = v_pn;

    if (pn->made != DEFERRED)
	return 0;

    if (MakeBuildChild(pn, toBeMade_next) == 0) {
	/* Mark so that when this node is built we reschedule its parents */
	pn->flags |= DONE_ORDER;
    }

    return 0;
}