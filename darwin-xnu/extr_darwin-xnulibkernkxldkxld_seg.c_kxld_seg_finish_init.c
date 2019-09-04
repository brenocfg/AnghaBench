#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  scalar_t__ kxld_size_t ;
typedef  scalar_t__ kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_10__ {scalar_t__ base_addr; scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ nitems; } ;
struct TYPE_9__ {scalar_t__ base_addr; int /*<<< orphan*/  vmsize; TYPE_1__ sects; } ;
typedef  TYPE_2__ KXLDSeg ;
typedef  TYPE_3__ KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 TYPE_3__* get_sect_by_index (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_round_page_cross_safe (scalar_t__) ; 
 int /*<<< orphan*/  require_action (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_seg_finish_init(KXLDSeg *seg)
{
    kern_return_t rval = KERN_FAILURE;
    u_int i = 0;
    KXLDSect *sect = NULL;
    kxld_addr_t maxaddr = 0;
    kxld_size_t maxsize = 0;

    /* If we already have a size for this segment (e.g. from the mach-o load
     * command) then don't recalculate the segment size. This is safer since 
     * when we recalculate we are making assumptions about page alignment and 
     * padding that the kext mach-o file was built with. Better to trust the 
     * macho-o info, if we have it. If we don't (i.e. vmsize == 0) then add up 
     * the section sizes and take a best guess at page padding.
     */
    if ((seg->vmsize == 0) && (seg->sects.nitems)) {
        for (i = 0; i < seg->sects.nitems; ++i) {
            sect = get_sect_by_index(seg, i);
            require_action(sect, finish, rval=KERN_FAILURE);
            if (sect->base_addr > maxaddr) {
                maxaddr = sect->base_addr;
                maxsize = sect->size;
            }
        }
        seg->vmsize = kxld_round_page_cross_safe(maxaddr +
                                                 maxsize - seg->base_addr);

    }

    rval = KERN_SUCCESS;
    
finish:
    return rval;
}