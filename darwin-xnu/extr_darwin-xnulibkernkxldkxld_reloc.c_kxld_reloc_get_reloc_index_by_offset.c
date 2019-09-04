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
typedef  scalar_t__ kxld_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {scalar_t__ nitems; } ;
struct TYPE_6__ {scalar_t__ address; } ;
typedef  TYPE_1__ KXLDReloc ;
typedef  TYPE_2__ KXLDArray ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* kxld_array_get_item (TYPE_2__ const*,scalar_t__) ; 

kern_return_t
kxld_reloc_get_reloc_index_by_offset(const KXLDArray *relocs, 
    kxld_size_t offset, u_int *idx)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDReloc *reloc = NULL;
    u_int i = 0;

    for (i = 0; i < relocs->nitems; ++i) {
        reloc = kxld_array_get_item(relocs, i);
        if (reloc->address == offset) break;
    }
    
    if (i >= relocs->nitems) {
        rval = KERN_FAILURE;
        goto finish;
    }

    *idx = i;
    rval = KERN_SUCCESS;

finish:
    return rval;
}