#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_7__ {scalar_t__ nitems; } ;
struct TYPE_6__ {int /*<<< orphan*/  vtables_by_name; int /*<<< orphan*/  obsolete_symbols_by_name; int /*<<< orphan*/  defined_cxx_symbols_by_value; int /*<<< orphan*/  defined_symbols_by_name; TYPE_2__ dependencies; TYPE_2__ objects; int /*<<< orphan*/ * kext; } ;
typedef  int /*<<< orphan*/  KXLDObject ;
typedef  int /*<<< orphan*/  KXLDKext ;
typedef  TYPE_1__ KXLDContext ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 void* kxld_array_get_item (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_array_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  kxld_dict_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_kext_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_object_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_context(KXLDContext *context)
{
    KXLDObject * object = NULL;
    KXLDKext   * dep     = NULL;
    u_int i = 0;

    check(context);

    kxld_kext_clear(context->kext);
    
    for (i = 0; i < context->objects.nitems; ++i) {
        object = kxld_array_get_item(&context->objects, i);
        kxld_object_clear(object);
    }
    kxld_array_reset(&context->objects);

    for (i = 0; i < context->dependencies.nitems; ++i) {
        dep = kxld_array_get_item(&context->dependencies, i);
        kxld_kext_clear(dep);
    }
    kxld_array_reset(&context->dependencies);

    kxld_dict_clear(&context->defined_symbols_by_name);
    kxld_dict_clear(&context->defined_cxx_symbols_by_value);
    kxld_dict_clear(&context->obsolete_symbols_by_name);
    kxld_dict_clear(&context->vtables_by_name);
}