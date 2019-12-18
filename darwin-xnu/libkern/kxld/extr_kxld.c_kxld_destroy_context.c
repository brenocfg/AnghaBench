#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_10__ {scalar_t__ maxitems; } ;
struct TYPE_9__ {struct TYPE_9__* kext; int /*<<< orphan*/  vtables_by_name; int /*<<< orphan*/  obsolete_symbols_by_name; int /*<<< orphan*/  defined_cxx_symbols_by_value; int /*<<< orphan*/  defined_symbols_by_name; TYPE_6__ dependencies; TYPE_6__ objects; } ;
typedef  int /*<<< orphan*/  KXLDObject ;
typedef  TYPE_1__ KXLDKext ;
typedef  TYPE_1__ KXLDContext ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_deinit (TYPE_6__*) ; 
 void* kxld_array_get_slot (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kxld_kext_deinit (TYPE_1__*) ; 
 int kxld_kext_sizeof () ; 
 int /*<<< orphan*/  kxld_object_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_print_memory_report () ; 

void
kxld_destroy_context(KXLDContext *context)
{
    KXLDObject *object = NULL;
    KXLDKext *dep = NULL;
    u_int i = 0;

    check(context);

    kxld_kext_deinit(context->kext);

    for (i = 0; i < context->objects.maxitems; ++i) {
        object = kxld_array_get_slot(&context->objects, i);
        kxld_object_deinit(object);
    }
    kxld_array_deinit(&context->objects);

    for (i = 0; i < context->dependencies.maxitems; ++i) {
        dep = kxld_array_get_slot(&context->dependencies, i);
        kxld_kext_deinit(dep);
    }
    kxld_array_deinit(&context->dependencies);

    kxld_dict_deinit(&context->defined_symbols_by_name);
    kxld_dict_deinit(&context->defined_cxx_symbols_by_value);
    kxld_dict_deinit(&context->obsolete_symbols_by_name);
    kxld_dict_deinit(&context->vtables_by_name);

    kxld_free(context->kext, kxld_kext_sizeof());
    kxld_free(context, sizeof(*context));

    kxld_print_memory_report();
}