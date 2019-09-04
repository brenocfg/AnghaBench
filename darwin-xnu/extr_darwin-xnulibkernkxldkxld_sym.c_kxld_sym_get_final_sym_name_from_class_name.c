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
 char const* FINAL_CLASS_TOKEN ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  OSOBJ_PREFIX ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlcat (char*,char const*,scalar_t__) ; 
 scalar_t__ strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

kern_return_t
kxld_sym_get_final_sym_name_from_class_name(const char *class_name, 
    char final_sym_name[], u_long final_sym_name_len)
{
    kern_return_t rval = KERN_FAILURE;
    u_long outlen = 0;

    check(class_name);
    check(final_sym_name);

    outlen = strlcpy(final_sym_name, OSOBJ_PREFIX, final_sym_name_len);
    require_action(outlen < final_sym_name_len, finish, 
        rval=KERN_FAILURE);

    outlen = strlcat(final_sym_name, class_name, final_sym_name_len);
    require_action(outlen < final_sym_name_len, finish, 
        rval=KERN_FAILURE);

    outlen = strlcat(final_sym_name, FINAL_CLASS_TOKEN, final_sym_name_len);
    require_action(outlen < final_sym_name_len, finish, 
        rval=KERN_FAILURE);

    rval = KERN_SUCCESS;

finish:
    return rval;
}