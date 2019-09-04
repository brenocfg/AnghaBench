#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  kext; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  TYPE_1__ KXLDSym ;
typedef  TYPE_2__ KXLDKext ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kKxldLogErr ; 
 int /*<<< orphan*/  kKxldLogLinking ; 
 int /*<<< orphan*/  kxld_demangle (int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/  kxld_free (char*,size_t) ; 
 int /*<<< orphan*/  kxld_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kxld_object_get_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_sym_is_unresolved ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  require_noerr_action (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
validate_symbols(KXLDKext *kext)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    u_int error = FALSE;
    char *demangled_name = NULL;
    size_t demangled_length = 0;
    
    /* Check for any unresolved symbols */
    kxld_symtab_iterator_init(&iter, kxld_object_get_symtab(kext->kext), 
        kxld_sym_is_unresolved, FALSE);
    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        if (!error) {
            error = TRUE;
            kxld_log(kKxldLogLinking, kKxldLogErr, 
                "The following symbols are unresolved for this kext:");
        }
        kxld_log(kKxldLogLinking, kKxldLogErr, "\t%s", 
            kxld_demangle(sym->name, &demangled_name, &demangled_length));
    }
    require_noerr_action(error, finish, rval=KERN_FAILURE);

    rval = KERN_SUCCESS;

finish:
    if (demangled_name) kxld_free(demangled_name, demangled_length);
    return rval;
}