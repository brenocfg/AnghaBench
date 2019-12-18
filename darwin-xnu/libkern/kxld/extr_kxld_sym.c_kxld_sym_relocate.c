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
struct TYPE_7__ {int /*<<< orphan*/  sectnum; scalar_t__ link_addr; scalar_t__ base_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  relocated_sectnum; scalar_t__ base_addr; scalar_t__ link_addr; } ;
typedef  TYPE_1__ KXLDSym ;
typedef  TYPE_2__ KXLDSect ;

/* Variables and functions */
 scalar_t__ kxld_sym_is_section (TYPE_1__*) ; 

void
kxld_sym_relocate(KXLDSym *sym, const KXLDSect *sect)
{
    if (kxld_sym_is_section(sym)) {
        sym->link_addr = sym->base_addr - sect->base_addr + sect->link_addr;
        sym->relocated_sectnum = sect->sectnum;
    }
}