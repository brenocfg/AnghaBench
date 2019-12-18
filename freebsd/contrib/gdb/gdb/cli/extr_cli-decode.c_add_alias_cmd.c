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
struct cmd_list_element {int abbrev_flag; struct cmd_list_element* cmd_pointer; int /*<<< orphan*/  allow_unknown; int /*<<< orphan*/  prefixname; int /*<<< orphan*/  prefixlist; int /*<<< orphan*/  function; int /*<<< orphan*/  func; int /*<<< orphan*/  doc; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;

/* Variables and functions */
 struct cmd_list_element* add_cmd (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cmd_list_element**) ; 
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  delete_cmd (char*,struct cmd_list_element**) ; 
 struct cmd_list_element* lookup_cmd (char**,struct cmd_list_element*,char*,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct cmd_list_element *
add_alias_cmd (char *name, char *oldname, enum command_class class,
	       int abbrev_flag, struct cmd_list_element **list)
{
  /* Must do this since lookup_cmd tries to side-effect its first arg */
  char *copied_name;
  struct cmd_list_element *old;
  struct cmd_list_element *c;
  copied_name = (char *) alloca (strlen (oldname) + 1);
  strcpy (copied_name, oldname);
  old = lookup_cmd (&copied_name, *list, "", 1, 1);

  if (old == 0)
    {
      delete_cmd (name, list);
      return 0;
    }

  c = add_cmd (name, class, NULL, old->doc, list);
  /* NOTE: Both FUNC and all the FUNCTIONs need to be copied.  */
  c->func = old->func;
  c->function = old->function;
  c->prefixlist = old->prefixlist;
  c->prefixname = old->prefixname;
  c->allow_unknown = old->allow_unknown;
  c->abbrev_flag = abbrev_flag;
  c->cmd_pointer = old;
  return c;
}