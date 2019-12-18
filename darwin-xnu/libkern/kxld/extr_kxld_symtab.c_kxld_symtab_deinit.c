#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name_index; int /*<<< orphan*/  cxx_index; int /*<<< orphan*/  syms; } ;
typedef  TYPE_1__ KXLDSymtab ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_dict_deinit (int /*<<< orphan*/ *) ; 

void
kxld_symtab_deinit(KXLDSymtab *symtab)
{
    check(symtab);

    kxld_array_deinit(&symtab->syms);
    kxld_dict_deinit(&symtab->cxx_index);
    kxld_dict_deinit(&symtab->name_index);
    bzero(symtab, sizeof(*symtab));
}