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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  VTABLE_PREFIX ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlcat (char*,char const*,scalar_t__) ; 
 scalar_t__ strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

kern_return_t
kxld_sym_get_vtable_name_from_class_name(const char *class_name, 
    char vtable_name[], u_long vtable_name_len)
{
    kern_return_t rval = KERN_FAILURE;
    u_long outlen = 0;

    check(class_name);
    check(vtable_name);

    outlen = strlcpy(vtable_name, VTABLE_PREFIX, vtable_name_len);
    require_action(outlen < vtable_name_len, finish, 
        rval=KERN_FAILURE);

    outlen = strlcat(vtable_name, class_name, vtable_name_len);
    require_action(outlen < vtable_name_len, finish, 
        rval=KERN_FAILURE);

    rval = KERN_SUCCESS;
finish:
    return rval;
}