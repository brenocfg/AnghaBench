#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_16__ {scalar_t__ nitems; } ;
struct TYPE_18__ {TYPE_11__ vtables; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ KXLDVTable ;
typedef  TYPE_2__ const KXLDKext ;
typedef  TYPE_2__ const KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (TYPE_2__ const*) ; 
 int /*<<< orphan*/  create_vtables (TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  finish ; 
 TYPE_1__* kxld_array_get_item (TYPE_11__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_insert (TYPE_2__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_kext_export_vtables(KXLDKext *kext, const KXLDDict *defined_cxx_symbols,
    const KXLDDict *defined_symbols, KXLDDict *vtables)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDVTable *vtable = NULL;
    u_int i = 0;

    check(kext);
    check(defined_symbols);
    check(defined_cxx_symbols);
    check(vtables);

    rval = create_vtables(kext, defined_cxx_symbols, defined_symbols);
    require_noerr(rval, finish);

    for (i = 0; i < kext->vtables.nitems; ++i) {
        vtable = kxld_array_get_item(&kext->vtables, i);

        rval = kxld_dict_insert(vtables, vtable->name, vtable);
        require_noerr(rval, finish);
    }
    
    rval = KERN_SUCCESS;
finish:
    return rval;
}