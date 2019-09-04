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

/* Variables and functions */
 int /*<<< orphan*/  OSOBJ_PREFIX ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlcat (char*,char const*,scalar_t__) ; 
 scalar_t__ strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

u_long
kxld_sym_get_function_prefix_from_class_name(const char *class_name,
    char function_prefix[], u_long function_prefix_len)
{
    u_long rval = 0;
    u_long outlen = 0;

    check(class_name);
    check(function_prefix);

    outlen = strlcpy(function_prefix, OSOBJ_PREFIX, function_prefix_len);
    require(outlen < function_prefix_len, finish);

    outlen = strlcat(function_prefix, class_name, function_prefix_len);
    require(outlen < function_prefix_len, finish);

    rval = outlen;
finish:
    return rval;
}