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
typedef  int u_long ;
typedef  int u_int ;
struct nlist_64 {int dummy; } ;
struct nlist {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int /*<<< orphan*/  KXLDSymtab ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kxld_sym_is_defined_locally ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

u_long 
kxld_symtab_get_macho_data_size(const KXLDSymtab *symtab, boolean_t is_32_bit)
{
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    u_long size = 1; /* strtab start padding */
    u_int nsyms = 0;
    
    check(symtab); 

    kxld_symtab_iterator_init(&iter, symtab, 
        kxld_sym_is_defined_locally, FALSE);

    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        size += strlen(sym->name) + 1;
        ++nsyms;
    }

    if (is_32_bit) {
        size += nsyms * sizeof(struct nlist);
    } else {
        size += nsyms * sizeof(struct nlist_64);
    }

    size = (size + 7) & ~7;

    return size;
}