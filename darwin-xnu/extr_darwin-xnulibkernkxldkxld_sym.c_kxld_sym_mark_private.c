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
struct TYPE_4__ {int /*<<< orphan*/  is_external; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_PEXT ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 

void
kxld_sym_mark_private(KXLDSym *sym)
{
    check(sym);

    sym->type |= N_PEXT;
    sym->is_external = FALSE;
}