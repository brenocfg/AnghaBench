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
struct TYPE_3__ {int /*<<< orphan*/  symtab; } ;
typedef  int /*<<< orphan*/  const KXLDSym ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_symtab_get_sym_index (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* kxld_symtab_get_symbol_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static KXLDSym *
get_mutable_sym(const KXLDObject *object, const KXLDSym *sym)
{
    KXLDSym *rval = NULL;
    kern_return_t result = KERN_FAILURE;
    u_int i = 0;

    result = kxld_symtab_get_sym_index(object->symtab, sym, &i);
    require_noerr(result, finish);

    rval = kxld_symtab_get_symbol_by_index(object->symtab, i);
    require_action(rval == sym, finish, rval=NULL);

finish:
    return rval;
}