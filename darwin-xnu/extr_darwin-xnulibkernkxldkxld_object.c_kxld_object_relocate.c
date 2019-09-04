#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ nitems; } ;
struct TYPE_5__ {int /*<<< orphan*/  sects; int /*<<< orphan*/  symtab; TYPE_3__ segs; int /*<<< orphan*/  link_addr; } ;
typedef  int /*<<< orphan*/  KXLDSeg ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/ * kxld_array_get_item (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_seg_relocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_symtab_relocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_object_relocate(KXLDObject *object, kxld_addr_t link_address)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSeg *seg = NULL;
    u_int i = 0;

    check(object);

    object->link_addr = link_address;

    /* Relocate segments (which relocates the sections) */
    for (i = 0; i < object->segs.nitems; ++i) {
        seg = kxld_array_get_item(&object->segs, i);
        kxld_seg_relocate(seg, link_address);
    } // for...

    /* Relocate symbols */
    rval = kxld_symtab_relocate(object->symtab, &object->sects);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;
finish:
   return rval;
}