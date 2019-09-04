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
typedef  TYPE_2__* coalition_t ;
struct TYPE_4__ {int /*<<< orphan*/  ledger; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ r; } ;

/* Variables and functions */
 scalar_t__ COALITION_TYPE_RESOURCE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i_coal_resource_dealloc(coalition_t coal)
{
	assert(coal && coal->type == COALITION_TYPE_RESOURCE);
	ledger_dereference(coal->r.ledger);
}