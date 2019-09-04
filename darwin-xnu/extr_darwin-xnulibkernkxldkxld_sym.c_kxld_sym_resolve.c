#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int type; void* is_indirect; void* is_undefined; void* is_resolved; void* is_absolute; void* is_external; int /*<<< orphan*/  sectnum; int /*<<< orphan*/  link_addr; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  NO_SECT ; 
 int N_ABS ; 
 int N_EXT ; 
 void* TRUE ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 scalar_t__ kxld_sym_is_indirect (TYPE_1__*) ; 
 scalar_t__ kxld_sym_is_undefined (TYPE_1__*) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_sym_resolve(KXLDSym *sym, kxld_addr_t addr) 
{
    kern_return_t rval = KERN_FAILURE;

    check(sym);

    require_action(kxld_sym_is_undefined(sym) || kxld_sym_is_indirect(sym), 
        finish, rval=KERN_FAILURE);

    /* Set the n_list data types */

    sym->link_addr = addr;
    sym->type = N_ABS | N_EXT;
    sym->sectnum = NO_SECT;
 
    /* Set the predicate bits for an externally resolved symbol. */
    
    sym->is_external = TRUE;
    sym->is_absolute = TRUE;
    sym->is_resolved = TRUE;

    /* Clear the predicate bits for types that can be resolved */

    sym->is_undefined = FALSE;
    sym->is_indirect = FALSE;

    rval = KERN_SUCCESS;

finish:

    return rval;
}