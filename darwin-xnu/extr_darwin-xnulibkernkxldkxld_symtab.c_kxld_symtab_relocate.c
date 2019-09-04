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
struct TYPE_4__ {int /*<<< orphan*/  sectnum; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int /*<<< orphan*/  const KXLDSymtab ;
typedef  TYPE_1__ KXLDSym ;
typedef  int /*<<< orphan*/  KXLDSect ;
typedef  int /*<<< orphan*/  KXLDArray ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/ * kxld_array_get_item (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_sym_is_section ; 
 int /*<<< orphan*/  kxld_sym_relocate (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_action (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_symtab_relocate(KXLDSymtab *symtab, const KXLDArray *sectarray)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    const KXLDSect *sect = NULL;
    
    check(symtab);
    check(sectarray);

    kxld_symtab_iterator_init(&iter, symtab, kxld_sym_is_section, FALSE);

    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        sect = kxld_array_get_item(sectarray, sym->sectnum);
        require_action(sect, finish, rval=KERN_FAILURE);
        kxld_sym_relocate(sym, sect);
    }

    rval = KERN_SUCCESS;

finish:

    return rval;
}