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
struct cmd_list_element {int dummy; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;

/* Variables and functions */
 struct cmd_list_element* add_cmd (char*,int,void (*) (char*,int),char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdlist ; 

struct cmd_list_element *
add_com (char *name, enum command_class class, void (*fun) (char *, int),
	 char *doc)
{
  return add_cmd (name, class, fun, doc, &cmdlist);
}