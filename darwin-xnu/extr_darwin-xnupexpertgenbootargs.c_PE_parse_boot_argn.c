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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PE_parse_boot_argn_internal (char const*,void*,int,int /*<<< orphan*/ ) ; 

boolean_t
PE_parse_boot_argn(
	const char	*arg_string,
	void		*arg_ptr,
	int			max_len)
{
	return PE_parse_boot_argn_internal(arg_string, arg_ptr, max_len, FALSE);
}