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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  VTABLE_PREFIX ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  extract_inner_string (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_sym_get_class_name_from_vtable_name(const char *vtable_name,
    char class_name[], u_long class_name_len)
{
    kern_return_t rval = KERN_FAILURE;

    check(vtable_name);

    rval = extract_inner_string(vtable_name, VTABLE_PREFIX, NULL,
        class_name, class_name_len);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;
finish:
    return rval;
}