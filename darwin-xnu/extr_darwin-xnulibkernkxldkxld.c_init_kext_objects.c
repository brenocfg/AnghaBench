#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {size_t nitems; } ;
struct TYPE_8__ {int /*<<< orphan*/  defined_cxx_symbols_by_value; int /*<<< orphan*/ * kext; int /*<<< orphan*/  vtables_by_name; int /*<<< orphan*/  defined_symbols_by_name; TYPE_3__ dependencies; int /*<<< orphan*/  obsolete_symbols_by_name; } ;
struct TYPE_7__ {char const* kext_name; char const* interface_name; scalar_t__ is_direct_dependency; int /*<<< orphan*/  interface_size; int /*<<< orphan*/ * interface; int /*<<< orphan*/  kext_size; int /*<<< orphan*/ * kext; } ;
typedef  int /*<<< orphan*/  KXLDObject ;
typedef  int /*<<< orphan*/  KXLDKext ;
typedef  TYPE_1__ KXLDDependency ;
typedef  TYPE_2__ KXLDContext ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/ * get_object_for_file (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * kxld_array_get_item (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  kxld_kext_export_symbols (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_kext_export_vtables (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_kext_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  require_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
init_kext_objects(KXLDContext *context,
                  u_char *file,
                  u_long size,
                  const char *name,
                  KXLDDependency *dependencies,
                  u_int ndependencies)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDKext *kext = NULL;
    KXLDObject *kext_object = NULL;
    KXLDObject *interface_object = NULL;
    u_int i = 0;
    
    /* Create a kext object for each dependency.  If it's a direct dependency,
     * export its symbols by name by value.  If it's indirect, just export the
     * C++ symbols by value.
     */
    for (i = 0; i < ndependencies; ++i) {
        kext = kxld_array_get_item(&context->dependencies, i);
        kext_object = NULL;
        interface_object = NULL;
        
        kext_object = get_object_for_file(context, dependencies[i].kext,
                                          dependencies[i].kext_size, dependencies[i].kext_name);
        require_action(kext_object, finish, rval=KERN_FAILURE);
        
        if (dependencies[i].interface) {
            interface_object = get_object_for_file(context,
                                                   dependencies[i].interface, dependencies[i].interface_size,
                                                   dependencies[i].interface_name);
            require_action(interface_object, finish, rval=KERN_FAILURE);
        }
        
        rval = kxld_kext_init(kext, kext_object, interface_object);
        require_noerr(rval, finish);
        
        if (dependencies[i].is_direct_dependency) {
            rval = kxld_kext_export_symbols(kext,
                                            &context->defined_symbols_by_name,
                                            &context->obsolete_symbols_by_name,
                                            &context->defined_cxx_symbols_by_value);
            require_noerr(rval, finish);
        } else {
            rval = kxld_kext_export_symbols(kext,
                                            /* defined_symbols */ NULL, /* obsolete_symbols */ NULL,
                                            &context->defined_cxx_symbols_by_value);
            require_noerr(rval, finish);
        }
    }
    
    /* Export the vtables for all of the dependencies. */
    for (i = 0; i < context->dependencies.nitems; ++i) {
        kext = kxld_array_get_item(&context->dependencies, i);
        
        rval = kxld_kext_export_vtables(kext,
                                        &context->defined_cxx_symbols_by_value,
                                        &context->defined_symbols_by_name,
                                        &context->vtables_by_name);
        require_noerr(rval, finish);
    }
    
    /* Create a kext object for the kext we're linking and export its locally
     * defined C++ symbols.
     */
    kext_object = get_object_for_file(context, file, size, name);
    require_action(kext_object, finish, rval=KERN_FAILURE);
    
    rval = kxld_kext_init(context->kext, kext_object, /* interface */ NULL);
    require_noerr(rval, finish);
    
    rval = kxld_kext_export_symbols(context->kext,
                                    /* defined_symbols */ NULL, /* obsolete_symbols */ NULL, 
                                    &context->defined_cxx_symbols_by_value);
    require_noerr(rval, finish);
    
    rval = KERN_SUCCESS;
finish:
    return rval;
}