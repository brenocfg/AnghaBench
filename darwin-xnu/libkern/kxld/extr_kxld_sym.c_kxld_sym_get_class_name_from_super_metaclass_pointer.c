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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  OSOBJ_PREFIX ; 
 int /*<<< orphan*/  SUPER_METACLASS_POINTER_TOKEN ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  extract_inner_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_sym_is_super_metaclass_pointer (TYPE_1__ const*) ; 
 int /*<<< orphan*/  require_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_sym_get_class_name_from_super_metaclass_pointer(const KXLDSym *sym,
    char class_name[], u_long class_name_len)
{
    kern_return_t rval = KERN_FAILURE;

    check(sym);
    require_action(kxld_sym_is_super_metaclass_pointer(sym), finish, 
        rval=KERN_FAILURE);

    rval = extract_inner_string(sym->name, OSOBJ_PREFIX, 
        SUPER_METACLASS_POINTER_TOKEN, class_name, class_name_len);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;
finish:
    return rval;
}