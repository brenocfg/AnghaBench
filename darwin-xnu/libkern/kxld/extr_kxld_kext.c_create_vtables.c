#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {scalar_t__ nitems; } ;
struct TYPE_7__ {scalar_t__ vtables_created; TYPE_2__ vtables; int /*<<< orphan*/  kext; } ;
typedef  int /*<<< orphan*/  KXLDVTable ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int /*<<< orphan*/  KXLDSymtab ;
typedef  int /*<<< orphan*/  KXLDSym ;
typedef  TYPE_1__ KXLDKext ;
typedef  int /*<<< orphan*/  KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  get_vtable_syms_from_smcp (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * kxld_array_get_item (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_array_init (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  kxld_array_resize (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * kxld_object_get_symtab (int /*<<< orphan*/ ) ; 
 scalar_t__ kxld_object_is_linked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_sym_is_super_metaclass_pointer ; 
 int /*<<< orphan*/  kxld_sym_is_vtable ; 
 int /*<<< orphan*/ * kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int kxld_symtab_iterator_get_num_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_vtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t 
create_vtables(KXLDKext *kext, const KXLDDict *defined_cxx_symbols,
    const KXLDDict *defined_symbols)
{
    kern_return_t rval = KERN_FAILURE;
    const KXLDSymtab *symtab = NULL;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    KXLDSym *vtable_sym = NULL;
    KXLDSym *meta_vtable_sym = NULL;
    KXLDVTable *vtable = NULL;
    KXLDVTable *meta_vtable = NULL;
    u_int i = 0;
    u_int nvtables = 0;

    if (kext->vtables_created) {
        rval = KERN_SUCCESS;
        goto finish;
    }

    symtab = kxld_object_get_symtab(kext->kext);

    if (kxld_object_is_linked(kext->kext)) {
        /* Create a vtable object for every vtable symbol */
        kxld_symtab_iterator_init(&iter, symtab, kxld_sym_is_vtable, FALSE);
        nvtables = kxld_symtab_iterator_get_num_remaining(&iter);
    } else {
        /* We walk over the super metaclass pointer symbols because classes
         * with them are the only ones that need patching.  Then we double the
         * number of vtables we're expecting, because every pointer will have a
         * class vtable and a MetaClass vtable.
         */
        kxld_symtab_iterator_init(&iter, symtab, 
            kxld_sym_is_super_metaclass_pointer, FALSE);
        nvtables = kxld_symtab_iterator_get_num_remaining(&iter) * 2;
    }

    rval = kxld_array_init(&kext->vtables, sizeof(KXLDVTable), nvtables);
    require_noerr(rval, finish);

    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        if (kxld_object_is_linked(kext->kext)) {
            vtable_sym = sym;
            meta_vtable_sym = NULL;
            meta_vtable = NULL;
        } else {
            rval = get_vtable_syms_from_smcp(kext, defined_symbols, sym,
                &vtable_sym, &meta_vtable_sym);
            require_noerr(rval, finish);
        }

        vtable = kxld_array_get_item(&kext->vtables, i++);
        rval = kxld_vtable_init(vtable, vtable_sym, kext->kext, 
            defined_cxx_symbols);
        require_noerr(rval, finish);

        /* meta_vtable_sym will be null when we don't support strict
         * patching and can't find the metaclass vtable. If that's the
         * case, we just reduce the expect number of vtables by 1.
         */
        if (!kxld_object_is_linked(kext->kext)) {
            if (meta_vtable_sym) {
                meta_vtable = kxld_array_get_item(&kext->vtables, i++);
                rval = kxld_vtable_init(meta_vtable, meta_vtable_sym, 
                    kext->kext, defined_cxx_symbols);
                require_noerr(rval, finish);
            } else {
                kxld_array_resize(&kext->vtables, --nvtables);
                meta_vtable = NULL;
            }
        }
    }
    require_action(i == kext->vtables.nitems, finish, 
        rval=KERN_FAILURE);

    kext->vtables_created = TRUE;
    rval = KERN_SUCCESS;
finish:
    return rval;
}