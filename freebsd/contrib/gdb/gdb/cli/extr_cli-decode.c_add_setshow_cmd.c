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
typedef  int /*<<< orphan*/  var_types ;
struct cmd_list_element {int dummy; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;
typedef  int /*<<< orphan*/  cmd_sfunc_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  add_setshow_cmd_full (char*,int,int /*<<< orphan*/ ,void*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
add_setshow_cmd (char *name,
		 enum command_class class,
		 var_types var_type, void *var,
		 char *set_doc, char *show_doc,
		 cmd_sfunc_ftype *set_func, cmd_sfunc_ftype *show_func,
		 struct cmd_list_element **set_list,
		 struct cmd_list_element **show_list)
{
  add_setshow_cmd_full (name, class, var_type, var, set_doc, show_doc,
			set_func, show_func, set_list, show_list,
			NULL, NULL);
}