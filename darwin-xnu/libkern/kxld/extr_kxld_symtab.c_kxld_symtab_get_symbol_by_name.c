#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_9__ {scalar_t__ nitems; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_6__ syms; } ;
typedef  TYPE_1__ KXLDSymtab ;
typedef  TYPE_2__ KXLDSym ;

/* Variables and functions */
 TYPE_2__* kxld_array_get_item (TYPE_6__*,scalar_t__) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char const*) ; 

KXLDSym * 
kxld_symtab_get_symbol_by_name(const KXLDSymtab *symtab, const char *name)
{
    KXLDSym *sym = NULL;
    u_int i = 0;

    for (i = 0; i < symtab->syms.nitems; ++i) {
        sym = kxld_array_get_item(&symtab->syms, i);

        if (streq(sym->name, name)) {
            return sym;
        }
    }
    
    return NULL;
}