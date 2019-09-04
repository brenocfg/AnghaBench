#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  is_replaced; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 

void
kxld_sym_delete(KXLDSym *sym)
{
    check(sym);

    bzero(sym, sizeof(*sym));
    sym->is_replaced = TRUE;
}