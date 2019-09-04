#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {scalar_t__ nitems; } ;
struct TYPE_8__ {scalar_t__ vtable_index_created; int /*<<< orphan*/  vtable_index; TYPE_5__ vtables; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ KXLDVTable ;
typedef  TYPE_2__ KXLDKext ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  finish ; 
 TYPE_1__* kxld_array_get_item (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_dict_string_cmp ; 
 int /*<<< orphan*/  kxld_dict_string_hash ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
create_vtable_index(KXLDKext *kext)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDVTable *vtable = NULL;
    u_int i = 0;

    if (kext->vtable_index_created) {
        rval = KERN_SUCCESS;
        goto finish;
    }

    /* Map vtable names to the vtable structures */
    rval = kxld_dict_init(&kext->vtable_index, kxld_dict_string_hash, 
        kxld_dict_string_cmp, kext->vtables.nitems);
    require_noerr(rval, finish);

    for (i = 0; i < kext->vtables.nitems; ++i) {
        vtable = kxld_array_get_item(&kext->vtables, i);
        rval = kxld_dict_insert(&kext->vtable_index, vtable->name, vtable);
        require_noerr(rval, finish);
    }

    kext->vtable_index_created = TRUE;
    rval = KERN_SUCCESS;
finish:
    return rval;
}