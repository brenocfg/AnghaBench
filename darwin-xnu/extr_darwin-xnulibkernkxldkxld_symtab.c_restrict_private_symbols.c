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
typedef  size_t u_int ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int /*<<< orphan*/  KXLDSymtab ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char const* KXLD_KMOD_INFO_SYMBOL ; 
 char const* KXLD_OPERATOR_DELETE_ARRAY_SYMBOL ; 
 char const* KXLD_OPERATOR_DELETE_SYMBOL ; 
 char const* KXLD_OPERATOR_NEW_ARRAY_SYMBOL ; 
 char const* KXLD_OPERATOR_NEW_SYMBOL ; 
 size_t const_array_len (char const**) ; 
 int /*<<< orphan*/  kxld_sym_is_exported ; 
 int /*<<< orphan*/  kxld_sym_mark_private (TYPE_1__*) ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
restrict_private_symbols(KXLDSymtab *symtab)
{
    const char *private_symbols[] = {
        KXLD_KMOD_INFO_SYMBOL,
        KXLD_OPERATOR_NEW_SYMBOL,
        KXLD_OPERATOR_NEW_ARRAY_SYMBOL,
        KXLD_OPERATOR_DELETE_SYMBOL,
        KXLD_OPERATOR_DELETE_ARRAY_SYMBOL
    };
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    const char *name = NULL;
    u_int i = 0;
    
    kxld_symtab_iterator_init(&iter, symtab, kxld_sym_is_exported, FALSE);
    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        for (i = 0; i < const_array_len(private_symbols); ++i) {
            name = private_symbols[i];
            if (!streq(sym->name, name)) {
                continue;
            }

            kxld_sym_mark_private(sym);
        }
    }
}