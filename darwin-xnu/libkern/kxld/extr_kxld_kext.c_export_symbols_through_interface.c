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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  link_addr; int /*<<< orphan*/ * name; int /*<<< orphan*/ * alias; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int /*<<< orphan*/  KXLDSymtab ;
typedef  TYPE_1__ KXLDSym ;
typedef  int /*<<< orphan*/  KXLDObject ;
typedef  int /*<<< orphan*/  KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kKxldLogLinking ; 
 int /*<<< orphan*/  kKxldLogWarn ; 
 int /*<<< orphan*/  kxld_dict_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  kxld_object_get_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * kxld_object_get_symtab (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kxld_sym_is_cxx ; 
 int /*<<< orphan*/  kxld_sym_is_indirect ; 
 int /*<<< orphan*/  kxld_sym_is_obsolete ; 
 int /*<<< orphan*/  kxld_sym_is_undefined ; 
 TYPE_1__* kxld_symtab_get_locally_defined_symbol_by_name (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
export_symbols_through_interface(const KXLDObject *kext,
    const KXLDObject *interface, KXLDDict *defined_symbols_by_name,
    KXLDDict *obsolete_symbols_by_name, KXLDDict *defined_cxx_symbols_by_value)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    const KXLDSymtab *kext_symtab = NULL;
    const KXLDSymtab *interface_symtab = NULL;
    KXLDSym *kext_sym = NULL;
    const KXLDSym *interface_sym = NULL;

    check(kext);
    check(interface);

    kext_symtab = kxld_object_get_symtab(kext);
    interface_symtab = kxld_object_get_symtab(interface);

    if (defined_symbols_by_name) {
        /* Add exported symbols */
        (void) kxld_symtab_iterator_init(&iter, interface_symtab, 
            kxld_sym_is_undefined, FALSE);
        while ((interface_sym = kxld_symtab_iterator_get_next(&iter))) {
            kext_sym = kxld_symtab_get_locally_defined_symbol_by_name(kext_symtab, 
                interface_sym->name);
            if (!kext_sym) {
                kxld_log(kKxldLogLinking, kKxldLogWarn,
                    "In interface %s of %s, couldn't find symbol %s\n", 
                    kxld_object_get_name(interface), kxld_object_get_name(kext),
                    interface_sym->name);
                continue;
            }

            rval = kxld_dict_insert(defined_symbols_by_name, 
                kext_sym->name, kext_sym);
            require_noerr(rval, finish);
        }

        /* Add indirect symbols */
        (void) kxld_symtab_iterator_init(&iter, interface_symtab, 
            kxld_sym_is_indirect, FALSE);
        while ((interface_sym = kxld_symtab_iterator_get_next(&iter))) {
            kext_sym = kxld_symtab_get_locally_defined_symbol_by_name(kext_symtab, 
                interface_sym->alias);
            if (!kext_sym) {
                kxld_log(kKxldLogLinking, kKxldLogWarn,
                    "In interface %s of %s, couldn't find indirect symbol %s (%s)\n", 
                    kxld_object_get_name(interface), kxld_object_get_name(kext),
                    interface_sym->alias, interface_sym->name);
                continue;
            }

            rval = kxld_dict_insert(defined_symbols_by_name, 
                interface_sym->name, kext_sym);
            require_noerr(rval, finish);
        }
    }

    /* Add obsolete symbols */
    if (obsolete_symbols_by_name) {
        (void) kxld_symtab_iterator_init(&iter, interface_symtab, 
            kxld_sym_is_obsolete, FALSE);
        while ((kext_sym = kxld_symtab_iterator_get_next(&iter))) {
            rval = kxld_dict_insert(obsolete_symbols_by_name, 
                kext_sym->name, kext_sym);
            require_noerr(rval, finish);
        }
    }

    /* Add C++ symbols */
    if (defined_cxx_symbols_by_value) {
        (void) kxld_symtab_iterator_init(&iter, kext_symtab,
            kxld_sym_is_cxx, FALSE);
        while ((kext_sym = kxld_symtab_iterator_get_next(&iter))) {
            rval = kxld_dict_insert(defined_cxx_symbols_by_value,
                &kext_sym->link_addr, kext_sym);
            require_noerr(rval, finish);
        }
    }

    rval = KERN_SUCCESS;
finish:
    return rval;
}