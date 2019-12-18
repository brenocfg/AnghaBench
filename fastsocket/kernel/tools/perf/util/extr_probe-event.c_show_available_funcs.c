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
struct strfilter {int dummy; } ;

/* Variables and functions */
 struct strfilter* available_func_filter ; 
 int available_kernel_funcs (char const*) ; 
 int available_user_funcs (char const*) ; 
 int /*<<< orphan*/  setup_pager () ; 

int show_available_funcs(const char *target, struct strfilter *_filter,
					bool user)
{
	setup_pager();
	available_func_filter = _filter;

	if (!user)
		return available_kernel_funcs(target);

	return available_user_funcs(target);
}