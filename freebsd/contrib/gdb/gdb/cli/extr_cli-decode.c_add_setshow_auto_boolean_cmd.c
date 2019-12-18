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
struct cmd_list_element {char const** enums; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;
typedef  enum auto_boolean { ____Placeholder_auto_boolean } auto_boolean ;
typedef  int /*<<< orphan*/  cmd_sfunc_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  add_setshow_cmd_full (char*,int,int /*<<< orphan*/ ,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**,struct cmd_list_element**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_auto_boolean ; 

void
add_setshow_auto_boolean_cmd (char *name,
			      enum command_class class,
			      enum auto_boolean *var,
			      char *set_doc, char *show_doc,
			      cmd_sfunc_ftype *set_func,
			      cmd_sfunc_ftype *show_func,
			      struct cmd_list_element **set_list,
			      struct cmd_list_element **show_list)
{
  static const char *auto_boolean_enums[] = { "on", "off", "auto", NULL };
  struct cmd_list_element *c;
  add_setshow_cmd_full (name, class, var_auto_boolean, var,
			set_doc, show_doc, set_func, show_func,
			set_list, show_list,
			&c, NULL);
  c->enums = auto_boolean_enums;
}