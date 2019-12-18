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
typedef  int boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  is_resolved; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 scalar_t__ kxld_sym_is_defined (TYPE_1__ const*) ; 

boolean_t
kxld_sym_is_defined_locally(const KXLDSym *sym)
{
    check(sym);

    return (kxld_sym_is_defined(sym) && !sym->is_resolved);
}