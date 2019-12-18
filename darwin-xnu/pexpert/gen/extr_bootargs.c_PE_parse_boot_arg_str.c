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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PE_parse_boot_argn_internal (char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
PE_parse_boot_arg_str(
	const char	*arg_string,
	char		*arg_ptr,
	int			strlen)
{
	return PE_parse_boot_argn_internal(arg_string, arg_ptr, strlen, TRUE);
}