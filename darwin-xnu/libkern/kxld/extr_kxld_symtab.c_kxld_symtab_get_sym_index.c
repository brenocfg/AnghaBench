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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  syms; } ;
typedef  TYPE_1__ KXLDSymtab ;
typedef  int /*<<< orphan*/  KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_array_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_symtab_get_sym_index(const KXLDSymtab *symtab, const KXLDSym *sym,
    u_int *symindex)
{
    kern_return_t rval = KERN_FAILURE;

    rval = kxld_array_get_index(&symtab->syms, sym, symindex);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;

finish:
    return rval;
}