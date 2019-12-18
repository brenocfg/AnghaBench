#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  vmsize; } ;
typedef  int /*<<< orphan*/  KXLDSymtab ;
typedef  TYPE_1__ KXLDSeg ;
typedef  int /*<<< orphan*/  KXLDArray ;

/* Variables and functions */
 scalar_t__ kxld_reloc_get_macho_data_size (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kxld_round_page_cross_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ kxld_symtab_get_macho_data_size (int /*<<< orphan*/  const*,scalar_t__) ; 

void 
kxld_seg_populate_linkedit(KXLDSeg *seg, const KXLDSymtab *symtab, boolean_t is_32_bit 
#if KXLD_PIC_KEXTS
    , const KXLDArray *locrelocs
    , const KXLDArray *extrelocs
    , boolean_t target_supports_slideable_kexts
#endif  /* KXLD_PIC_KEXTS */
    , uint32_t splitinfolc_size
   )
{
    u_long size = 0;

    size += kxld_symtab_get_macho_data_size(symtab, is_32_bit);

#if KXLD_PIC_KEXTS
    if (target_supports_slideable_kexts) {
        size += kxld_reloc_get_macho_data_size(locrelocs, extrelocs);
    }
#endif	/* KXLD_PIC_KEXTS */

    // 0 unless this is a split kext
    size += splitinfolc_size;

    seg->vmsize = kxld_round_page_cross_safe(size);
}