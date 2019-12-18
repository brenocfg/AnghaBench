#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {scalar_t__ nitems; } ;
struct TYPE_8__ {scalar_t__ kextSize; int /*<<< orphan*/ * kextExecutable; } ;
struct TYPE_9__ {scalar_t__ target_order; scalar_t__ host_order; int /*<<< orphan*/ * section_order; void* got_is_created; void* is_linked; void* is_final_image; void* is_kernel; scalar_t__ cpusubtype; scalar_t__ cputype; scalar_t__ filetype; TYPE_1__ split_info; int /*<<< orphan*/  splitinfolc; scalar_t__ size; int /*<<< orphan*/ * file; scalar_t__ symtab; int /*<<< orphan*/  srcversion; int /*<<< orphan*/  versionmin; int /*<<< orphan*/  uuid; int /*<<< orphan*/  relocator; TYPE_5__ locrelocs; TYPE_5__ extrelocs; TYPE_5__ sects; TYPE_5__ segs; } ;
typedef  int /*<<< orphan*/  KXLDSeg ;
typedef  int /*<<< orphan*/  KXLDSect ;
typedef  TYPE_2__ KXLDObject ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  check (TYPE_2__*) ; 
 scalar_t__ isOldInterface ; 
 void* kxld_array_get_item (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_array_reset (TYPE_5__*) ; 
 scalar_t__ kxld_object_is_kernel (TYPE_2__*) ; 
 int /*<<< orphan*/  kxld_relocator_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_sect_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_seg_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_splitinfolc_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_srcversion_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_clear (scalar_t__) ; 
 int /*<<< orphan*/  kxld_uuid_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_versionmin_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unswap_macho (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void kxld_object_clear(KXLDObject *object)
{
    KXLDSeg *seg = NULL;
    KXLDSect *sect = NULL;
    u_int i;
    u_char *my_file;
    
    check(object);

    if (isOldInterface) {
        my_file = object->file;
    }
    else {
        my_file = object->split_info.kextExecutable;
    }

#if !KERNEL
    if (kxld_object_is_kernel(object)) {
        unswap_macho(my_file, object->host_order, object->target_order);
    }
#endif /* !KERNEL */

    for (i = 0; i < object->segs.nitems; ++i) {
        seg = kxld_array_get_item(&object->segs, i);
        kxld_seg_clear(seg);
    }
    kxld_array_reset(&object->segs);

    for (i = 0; i < object->sects.nitems; ++i) {
        sect = kxld_array_get_item(&object->sects, i);
        kxld_sect_clear(sect);
    }
    kxld_array_reset(&object->sects);

    kxld_array_reset(&object->extrelocs);
    kxld_array_reset(&object->locrelocs);
    kxld_relocator_clear(&object->relocator);
    kxld_uuid_clear(&object->uuid);
    kxld_versionmin_clear(&object->versionmin);
    kxld_srcversion_clear(&object->srcversion);

    if (object->symtab) kxld_symtab_clear(object->symtab);

    if (isOldInterface) {
        object->file = NULL;
        object->size = 0;
    }
    else {
        kxld_splitinfolc_clear(&object->splitinfolc);
        object->split_info.kextExecutable = NULL;
        object->split_info.kextSize = 0;
    }
    object->filetype = 0;
    object->cputype = 0;
    object->cpusubtype = 0;
    object->is_kernel = FALSE;
    object->is_final_image = FALSE;
    object->is_linked = FALSE;
    object->got_is_created = FALSE;

#if KXLD_USER_OR_OBJECT
    object->section_order = NULL;
#endif
#if !KERNEL
    object->host_order = 0;
    object->target_order = 0;
#endif
}