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
typedef  scalar_t__ u_int ;
struct TYPE_4__ {int is_absolute; scalar_t__ is_section; scalar_t__ sectnum; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 scalar_t__ kxld_sym_is_section (TYPE_1__*) ; 

__attribute__((used)) static void
init_sym_sectnum(KXLDSym *sym, u_int n_sect)
{
    /* The n_sect field is set to 0 when the symbol is not section-based, and
     * the number of the section in which the symbol exists otherwise.
     * Sometimes, symbols can be labeled as section-based, so we make sure that
     * they have a valid section number, and set them as absolute if they don't.
     */

    if (kxld_sym_is_section(sym)) {
        if (n_sect) {
            /* Convert the section number to an index into the section index */
            sym->sectnum = n_sect - 1;
        } else {
            sym->is_absolute = 1;
            sym->is_section = 0;
        }
    }

}