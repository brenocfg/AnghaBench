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
typedef  int /*<<< orphan*/  kxld_addr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  symtab; } ;
typedef  int /*<<< orphan*/  KXLDSym ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_symtab_add_symbol (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_object_add_symbol(KXLDObject *object, char *name, kxld_addr_t link_addr, 
    const KXLDSym **sym_out)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSym *sym = NULL;

    rval = kxld_symtab_add_symbol(object->symtab, name, link_addr, &sym);
    require_noerr(rval, finish);

    *sym_out = sym;
    rval = KERN_SUCCESS;
finish:
    return rval;
}