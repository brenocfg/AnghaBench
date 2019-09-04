#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dtp_refcnt; TYPE_1__* dtp_difo; } ;
typedef  TYPE_2__ dtrace_predicate_t ;
struct TYPE_4__ {scalar_t__ dtdo_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static void
dtrace_predicate_hold(dtrace_predicate_t *pred)
{
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	ASSERT(pred->dtp_difo != NULL && pred->dtp_difo->dtdo_refcnt != 0);
	ASSERT(pred->dtp_refcnt > 0);

	pred->dtp_refcnt++;
}