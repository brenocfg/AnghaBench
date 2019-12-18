#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int ;
struct TYPE_9__ {scalar_t__ nitems; } ;
struct TYPE_8__ {int /*<<< orphan*/  extrelocs; int /*<<< orphan*/  locrelocs; int /*<<< orphan*/  symtab; TYPE_5__ segs; } ;
typedef  int /*<<< orphan*/  KXLDSeg ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  SEG_LINKEDIT ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * kxld_array_get_item (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/ * kxld_object_get_seg_by_name (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_object_is_32_bit (TYPE_1__ const*) ; 
 scalar_t__ kxld_reloc_get_macho_data_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kxld_round_page_cross_safe (scalar_t__) ; 
 scalar_t__ kxld_seg_get_vmsize (int /*<<< orphan*/ *) ; 
 scalar_t__ kxld_symtab_get_macho_data_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_supports_slideable_kexts (TYPE_1__ const*) ; 

__attribute__((used)) static u_long
get_macho_data_size(const KXLDObject *object)
{
    KXLDSeg *seg = NULL;
    u_long data_size = 0;
    u_int i = 0;

    check(object);

    /* total all segment vmsize values */
    for (i = 0; i < object->segs.nitems; ++i) {
        seg = kxld_array_get_item(&object->segs, i);
        data_size += (u_long) kxld_seg_get_vmsize(seg);
    }

#if KXLD_PIC_KEXTS
    {
        /* ensure that when we eventually emit the final linked object, 
         * appending the __DYSYMTAB data after the __LINKEDIT data will
         * not overflow the space allocated for the __LINKEDIT segment
         */
        
        u_long  seg_vmsize = 0;
        u_long  symtab_size = 0;
        u_long  reloc_size = 0;
        
        /* get current __LINKEDIT sizes */
        seg = kxld_object_get_seg_by_name(object, SEG_LINKEDIT);
        
        seg_vmsize = (u_long) kxld_seg_get_vmsize(seg);
         
        /* get size of symbol table data that will eventually be dumped
         * into the __LINKEDIT segment
         */
        symtab_size = kxld_symtab_get_macho_data_size(object->symtab, kxld_object_is_32_bit(object));
        
        if (target_supports_slideable_kexts(object)) {
            /* get size of __DYSYMTAB relocation entries */
            reloc_size = kxld_reloc_get_macho_data_size(&object->locrelocs, &object->extrelocs);
        }
        
        /* combine, and ensure they'll both fit within the page(s)
         * allocated for the __LINKEDIT segment. If they'd overflow,
         * increase the vmsize appropriately so no overflow will occur
         */
        if ((symtab_size + reloc_size) > seg_vmsize) {
            u_long  overflow = (symtab_size + reloc_size) - seg_vmsize;
            data_size += kxld_round_page_cross_safe(overflow);
        }
    }
#endif  // KXLD_PIC_KEXTS

    return data_size;
}