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
 int /*<<< orphan*/  METACLASS_VTABLE_PREFIX ; 
 char const* METACLASS_VTABLE_SUFFIX ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlcat (char*,char const*,scalar_t__) ; 
 scalar_t__ strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

kern_return_t
kxld_sym_get_meta_vtable_name_from_class_name(const char *class_name, 
    char meta_vtable_name[], u_long meta_vtable_name_len)
{
    kern_return_t rval = KERN_FAILURE;
    u_long outlen = 0;

    check(class_name);
    check(meta_vtable_name);

    outlen = strlcpy(meta_vtable_name, METACLASS_VTABLE_PREFIX,
        meta_vtable_name_len);
    require_action(outlen < meta_vtable_name_len, finish,
        rval=KERN_FAILURE);

    outlen = strlcat(meta_vtable_name, class_name, meta_vtable_name_len);
    require_action(outlen < meta_vtable_name_len, finish, 
        rval=KERN_FAILURE);

    outlen = strlcat(meta_vtable_name, METACLASS_VTABLE_SUFFIX, 
        meta_vtable_name_len);
    require_action(outlen < meta_vtable_name_len, finish, 
        rval=KERN_FAILURE);

    rval = KERN_SUCCESS;
finish:
    return rval;
}