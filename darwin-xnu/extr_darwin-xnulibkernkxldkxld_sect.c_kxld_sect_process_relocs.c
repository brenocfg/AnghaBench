#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ nitems; } ;
struct TYPE_5__ {TYPE_4__ relocs; } ;
typedef  TYPE_1__ KXLDSect ;
typedef  int /*<<< orphan*/  KXLDRelocator ;
typedef  int /*<<< orphan*/  KXLDReloc ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/ * kxld_array_get_item (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_relocator_process_sect_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_sect_process_relocs(KXLDSect *sect, KXLDRelocator *relocator)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDReloc *reloc = NULL;
    u_int i = 0;

    for (i = 0; i < sect->relocs.nitems; ++i) {
        reloc = kxld_array_get_item(&sect->relocs, i);
        rval = kxld_relocator_process_sect_reloc(relocator, reloc, sect);
        require_noerr(rval, finish);
    }

    rval = KERN_SUCCESS;
finish:
    return rval;
}