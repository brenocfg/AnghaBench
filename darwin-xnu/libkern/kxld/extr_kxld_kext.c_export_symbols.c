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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {int /*<<< orphan*/  link_addr; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  TYPE_1__ KXLDSym ;
typedef  int /*<<< orphan*/  KXLDObject ;
typedef  int /*<<< orphan*/  KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_dict_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_object_get_symtab (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_sym_is_cxx (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_sym_is_exported ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
export_symbols(const KXLDObject *kext, KXLDDict *defined_symbols_by_name,
    KXLDDict *defined_cxx_symbols_by_value)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;

    (void) kxld_symtab_iterator_init(&iter, kxld_object_get_symtab(kext), 
        kxld_sym_is_exported, FALSE);
    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        if (defined_symbols_by_name) {
            rval = kxld_dict_insert(defined_symbols_by_name, sym->name, sym);
            require_noerr(rval, finish);
        }

        if (kxld_sym_is_cxx(sym) && defined_cxx_symbols_by_value) {
            rval = kxld_dict_insert(defined_cxx_symbols_by_value,
                &sym->link_addr, sym);
            require_noerr(rval, finish);
        }
    }

    rval = KERN_SUCCESS;
finish:
    return rval;
}