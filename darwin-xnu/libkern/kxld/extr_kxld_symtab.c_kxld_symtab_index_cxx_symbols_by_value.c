#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {int /*<<< orphan*/  base_addr; } ;
struct TYPE_8__ {scalar_t__ cxx_index_initialized; int /*<<< orphan*/  cxx_index; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  TYPE_1__ KXLDSymtab ;
typedef  TYPE_2__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_dict_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_dict_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kxld_dict_kxldaddr_cmp ; 
 int /*<<< orphan*/  kxld_dict_kxldaddr_hash ; 
 TYPE_2__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_get_num_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_is_defined_cxx ; 

kern_return_t
kxld_symtab_index_cxx_symbols_by_value(KXLDSymtab *symtab)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    u_int nsyms = 0;

    check(symtab);

    if (symtab->cxx_index_initialized) {
        rval = KERN_SUCCESS;
        goto finish;
    }

    /* Count the number of C++ symbols */
    kxld_symtab_iterator_init(&iter, symtab, sym_is_defined_cxx, FALSE);
    nsyms = kxld_symtab_iterator_get_num_remaining(&iter);

    /* Create the dictionary */
    rval = kxld_dict_init(&symtab->cxx_index, kxld_dict_kxldaddr_hash, 
        kxld_dict_kxldaddr_cmp, nsyms);
    require_noerr(rval, finish);

    /* Insert the non-stab symbols */
    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        rval = kxld_dict_insert(&symtab->cxx_index, &sym->base_addr, sym);
        require_noerr(rval, finish);
    }
    
    
    symtab->cxx_index_initialized = TRUE;
    rval = KERN_SUCCESS;
finish:
    return rval;
}