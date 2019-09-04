#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ kxld_addr_t ;
struct TYPE_4__ {scalar_t__ link_addr; } ;
typedef  TYPE_1__ KXLDSect ;

/* Variables and functions */
 scalar_t__ kxld_sect_align_address (TYPE_1__*,scalar_t__) ; 

void
kxld_sect_relocate(KXLDSect *sect, kxld_addr_t link_addr)
{
#if SPLIT_KEXTS_DEBUG
    {
        kxld_log(kKxldLogLinking, kKxldLogErr,
                 "%p >>> Start of %s section (sect->size %llu) <%s>",
                 (void *) (kxld_sect_align_address(sect, sect->link_addr + link_addr)),
                 sect->sectname[0] ? sect->sectname : "none",
                 sect->size,
                 __func__);
        kxld_log(kKxldLogLinking, kKxldLogErr,
                 "%p <<< End of %s section <%s>",
                 (void *) (kxld_sect_align_address(sect, sect->link_addr + link_addr) + sect->size),
                 sect->sectname[0] ? sect->sectname : "none",
                 __func__);
    }
#endif

    sect->link_addr = kxld_sect_align_address(sect,
                                              sect->link_addr + link_addr);
}