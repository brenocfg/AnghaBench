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
typedef  int /*<<< orphan*/  kxld_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  cxx_index; } ;
typedef  TYPE_1__ KXLDSymtab ;
typedef  int /*<<< orphan*/  KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * kxld_dict_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

KXLDSym *
kxld_symtab_get_cxx_symbol_by_value(const KXLDSymtab *symtab, kxld_addr_t value)
{
    check(symtab);

    return kxld_dict_find(&symtab->cxx_index, &value);
}