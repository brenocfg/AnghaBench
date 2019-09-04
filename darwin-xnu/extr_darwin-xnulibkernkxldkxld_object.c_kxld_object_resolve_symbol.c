#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  KXLDSym ;
typedef  int /*<<< orphan*/  KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/ * get_mutable_sym (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kxld_sym_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_object_resolve_symbol(KXLDObject *object, 
    const KXLDSym *sym, kxld_addr_t addr)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSym *resolved_sym = NULL;

    resolved_sym = get_mutable_sym(object, sym);
    require_action(resolved_sym, finish, rval=KERN_FAILURE);

    rval = kxld_sym_resolve(resolved_sym, addr);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;
finish:
    return rval;
}