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

/* Variables and functions */
 struct cmd_list_element* add_set_or_show_cmd (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,char*,struct cmd_list_element**) ; 
 int /*<<< orphan*/  set_cmd ; 

struct cmd_list_element *
add_set_cmd (char *name,
	     enum command_class class,
	     var_types var_type,
	     void *var,
	     char *doc,
	     struct cmd_list_element **list)
{
  return add_set_or_show_cmd (name, set_cmd, class, var_type, var, doc, list);
}