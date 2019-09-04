#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {TYPE_1__* l_template; int /*<<< orphan*/  l_refs; } ;
struct TYPE_7__ {scalar_t__ lt_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LEDGER_VALID (TYPE_2__*) ; 
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_ledger_free (TYPE_2__*) ; 
 int /*<<< orphan*/  zfree (scalar_t__,TYPE_2__*) ; 

kern_return_t
ledger_dereference(ledger_t ledger)
{
	int v;

	if (!LEDGER_VALID(ledger))
		return (KERN_INVALID_ARGUMENT);

	v = OSDecrementAtomic(&ledger->l_refs);
	ASSERT(v >= 1);

	/* Just released the last reference.  Free it. */
	if (v == 1) {
		if (ledger->l_template->lt_zone) {
			zfree(ledger->l_template->lt_zone, ledger);
		} else {
			pmap_ledger_free(ledger);
		}
	}

	return (KERN_SUCCESS);
}