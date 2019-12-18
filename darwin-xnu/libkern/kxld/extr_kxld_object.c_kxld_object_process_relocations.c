#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {scalar_t__ is_final_image; int /*<<< orphan*/  relocator; } ;
typedef  TYPE_1__ KXLDObject ;
typedef  int /*<<< orphan*/  KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_relocator_set_vtables (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  populate_got (TYPE_1__*) ; 
 int /*<<< orphan*/  populate_kmod_info (TYPE_1__*) ; 
 int /*<<< orphan*/  process_relocs_from_sections (TYPE_1__*) ; 
 int /*<<< orphan*/  process_relocs_from_tables (TYPE_1__*) ; 
 int /*<<< orphan*/  process_symbol_pointers (TYPE_1__*) ; 
 int /*<<< orphan*/  require_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_object_process_relocations(KXLDObject *object, 
    const KXLDDict *patched_vtables)
{
    kern_return_t rval = KERN_FAILURE;

    (void) kxld_relocator_set_vtables(&object->relocator, patched_vtables);

    /* Process relocation entries and populate the global offset table.
     *
     * For final linked images: the relocation entries are contained in a couple
     * of tables hanging off the end of the symbol table.  The GOT has its own
     * section created by the linker; we simply need to fill it.
     *
     * For object files: the relocation entries are bound to each section.
     * The GOT, if it exists for the target architecture, is created by kxld,
     * and we must populate it according to our internal structures.
     */
    if (object->is_final_image) {
#if KXLD_USER_OR_BUNDLE
        rval = process_symbol_pointers(object);
        require_noerr(rval, finish);

        rval = process_relocs_from_tables(object);
        require_noerr(rval, finish);
#else
        require_action(FALSE, finish, rval=KERN_FAILURE);
#endif /* KXLD_USER_OR_BUNDLE */
    } else {
#if KXLD_USER_OR_GOT
        /* Populate GOT */
        rval = populate_got(object);
        require_noerr(rval, finish);
#endif /* KXLD_USER_OR_GOT */
#if KXLD_USER_OR_OBJECT
        rval = process_relocs_from_sections(object);
        require_noerr(rval, finish);
#else
        require_action(FALSE, finish, rval=KERN_FAILURE);
#endif /* KXLD_USER_OR_OBJECT */
    }

    /* Populate kmod info structure */
    rval = populate_kmod_info(object);
    require_noerr(rval, finish);
 
    rval = KERN_SUCCESS;
finish:
   return rval;
}