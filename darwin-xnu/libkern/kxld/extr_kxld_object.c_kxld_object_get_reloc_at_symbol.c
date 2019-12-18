#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  relocs; } ;
struct TYPE_13__ {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  locrelocs; int /*<<< orphan*/  extrelocs; int /*<<< orphan*/  sectnum; } ;
typedef  TYPE_1__ KXLDSym ;
typedef  TYPE_2__ KXLDSect ;
typedef  int /*<<< orphan*/  KXLDReloc ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  finish ; 
 TYPE_2__* kxld_object_get_section_by_index (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ kxld_object_is_final_image (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * kxld_reloc_get_reloc_by_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_sym_get_section_offset (TYPE_1__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  require (TYPE_2__ const*,int /*<<< orphan*/ ) ; 

const KXLDReloc * 
kxld_object_get_reloc_at_symbol(const KXLDObject *object, const KXLDSym *sym)
{
    const KXLDReloc *reloc = NULL;
    const KXLDSect *sect = NULL;
    uint32_t offset = 0;

    check(object);
    check(sym);

    sect = kxld_object_get_section_by_index(object, sym->sectnum);
    require(sect, finish);

    if (kxld_object_is_final_image(object)) {
        reloc = kxld_reloc_get_reloc_by_offset(&object->extrelocs, 
                                               sym->base_addr);
        if (!reloc) {
            reloc = kxld_reloc_get_reloc_by_offset(&object->locrelocs, 
                                                   sym->base_addr);
        }
    } else {
        offset = kxld_sym_get_section_offset(sym, sect);
        reloc = kxld_reloc_get_reloc_by_offset(&sect->relocs, offset);
    }

finish:
    return reloc;
}