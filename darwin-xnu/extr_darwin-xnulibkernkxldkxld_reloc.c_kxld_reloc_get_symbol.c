#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  kxld_addr_t ;
struct TYPE_8__ {int target_type; int /*<<< orphan*/  address; int /*<<< orphan*/  target; } ;
struct TYPE_7__ {int /*<<< orphan*/  symtab; } ;
typedef  int /*<<< orphan*/  KXLDSym ;
typedef  TYPE_1__ KXLDRelocator ;
typedef  TYPE_2__ KXLDReloc ;

/* Variables and functions */
#define  KXLD_TARGET_SECTNUM 129 
#define  KXLD_TARGET_SYMBOLNUM 128 
 int /*<<< orphan*/  check (TYPE_2__ const*) ; 
 int /*<<< orphan*/  kxld_relocator_get_pointer_at_addr (TYPE_1__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kxld_symtab_get_cxx_symbol_by_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kxld_symtab_get_symbol_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

KXLDSym *
kxld_reloc_get_symbol(const KXLDRelocator *relocator, const KXLDReloc *reloc,
    const u_char *data)
{
    KXLDSym *sym = NULL;
    kxld_addr_t value = 0;

    check(reloc);

    switch (reloc->target_type) {
    case KXLD_TARGET_SYMBOLNUM:
        sym = kxld_symtab_get_symbol_by_index(relocator->symtab, reloc->target);
        break;
    case KXLD_TARGET_SECTNUM:
       if (data) {
            value = kxld_relocator_get_pointer_at_addr(relocator, data,
                                                       reloc->address);
            sym = kxld_symtab_get_cxx_symbol_by_value(relocator->symtab, value);
       }
        break;
    default:
        sym = NULL;
        break;
    }

    return sym;
}