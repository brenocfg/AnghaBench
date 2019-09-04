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
typedef  TYPE_1__* ledger_t ;
struct TYPE_4__ {int l_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDGER_VALID (TYPE_1__*) ; 

int
ledger_reference_count(ledger_t ledger)
{
	if (!LEDGER_VALID(ledger))
		return (-1);

	return (ledger->l_refs);
}