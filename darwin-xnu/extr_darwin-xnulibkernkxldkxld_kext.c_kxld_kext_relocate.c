#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_19__ {int /*<<< orphan*/  kext; } ;
typedef  TYPE_1__ const KXLDKext ;
typedef  TYPE_1__ const KXLDDict ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  create_vtables (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish ; 
 scalar_t__ isSplitKext ; 
 int /*<<< orphan*/  kxld_object_index_cxx_symbols_by_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_object_index_symbols_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_object_process_relocations (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  kxld_object_relocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch_vtables (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_symbols (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  validate_symbols (TYPE_1__ const*) ; 

kern_return_t
kxld_kext_relocate(KXLDKext *kext,
                   kxld_addr_t link_address,
                   KXLDDict *patched_vtables,
                   const KXLDDict *defined_symbols,
                   const KXLDDict *obsolete_symbols,
                   const KXLDDict *defined_cxx_symbols)
{
    kern_return_t rval = KERN_FAILURE;

    check(kext);
    check(patched_vtables);
    check(defined_symbols);
    check(obsolete_symbols);

    /* Kexts that are being relocated need symbols indexed by value for vtable
     * creation and patching. Note that we don't need to index by value for
     * dependencies that have already been linked because their symbols are
     * already in the global cxx value table. It's important to index the
     * symbols by value before we relocate the symbols because the vtable
     * entries will still have unrelocated values.
     */
    rval = kxld_object_index_cxx_symbols_by_value(kext->kext);
    require_noerr(rval, finish);

    rval = kxld_object_index_symbols_by_name(kext->kext);
    require_noerr(rval, finish);

    rval = kxld_object_relocate(kext->kext, link_address);
    require_noerr(rval, finish);

    rval = resolve_symbols(kext, defined_symbols, obsolete_symbols);
    require_noerr(rval, finish);

    rval = create_vtables(kext, defined_cxx_symbols, /* defined_symbols */ NULL);
    require_noerr(rval, finish);

    if (isSplitKext == FALSE) {
        rval = patch_vtables(kext, patched_vtables, defined_symbols);
        require_noerr(rval, finish);
    }
 
    rval = validate_symbols(kext);
    require_noerr(rval, finish);

    rval = kxld_object_process_relocations(kext->kext, patched_vtables);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;
finish:
   return rval;
}