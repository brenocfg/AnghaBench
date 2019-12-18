#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_8__ {scalar_t__ maxitems; } ;
struct TYPE_7__ {int /*<<< orphan*/  vtable_index; TYPE_3__ vtables; } ;
typedef  int /*<<< orphan*/  KXLDVTable ;
typedef  TYPE_1__ KXLDKext ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_deinit (TYPE_3__*) ; 
 int /*<<< orphan*/ * kxld_array_get_slot (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_vtable_deinit (int /*<<< orphan*/ *) ; 

void 
kxld_kext_deinit(KXLDKext *kext)
{
    KXLDVTable *vtable = NULL;
    u_int i;

    check(kext);

    for (i = 0; i < kext->vtables.maxitems; ++i) {
        vtable = kxld_array_get_slot(&kext->vtables, i);
        kxld_vtable_deinit(vtable);
    }
    kxld_array_deinit(&kext->vtables);
    kxld_dict_deinit(&kext->vtable_index);

    bzero(kext, sizeof(*kext));
}