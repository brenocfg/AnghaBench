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
struct cmd_list_element {char* name; int class; char* doc; int /*<<< orphan*/ * cmd_pointer; int /*<<< orphan*/ * hookee_post; int /*<<< orphan*/ * hookee_pre; int /*<<< orphan*/ * user_commands; int /*<<< orphan*/ * enums; int /*<<< orphan*/  var_type; int /*<<< orphan*/ * var; int /*<<< orphan*/  type; scalar_t__ abbrev_flag; scalar_t__ allow_unknown; int /*<<< orphan*/ * prefixname; int /*<<< orphan*/ * prefixlist; scalar_t__ hook_in; int /*<<< orphan*/ * hook_post; int /*<<< orphan*/ * hook_pre; int /*<<< orphan*/ * pre_show_hook; int /*<<< orphan*/ * replacement; scalar_t__ flags; struct cmd_list_element* next; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;

/* Variables and functions */
 int /*<<< orphan*/  delete_cmd (char*,struct cmd_list_element**) ; 
 int /*<<< orphan*/  make_symbol_completion_list ; 
 int /*<<< orphan*/  not_set_cmd ; 
 int /*<<< orphan*/  set_cmd_cfunc (struct cmd_list_element*,void (*) (char*,int)) ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_context (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  var_boolean ; 
 scalar_t__ xmalloc (int) ; 

struct cmd_list_element *
add_cmd (char *name, enum command_class class, void (*fun) (char *, int),
	 char *doc, struct cmd_list_element **list)
{
  struct cmd_list_element *c
  = (struct cmd_list_element *) xmalloc (sizeof (struct cmd_list_element));
  struct cmd_list_element *p;

  delete_cmd (name, list);

  if (*list == NULL || strcmp ((*list)->name, name) >= 0)
    {
      c->next = *list;
      *list = c;
    }
  else
    {
      p = *list;
      while (p->next && strcmp (p->next->name, name) <= 0)
	{
	  p = p->next;
	}
      c->next = p->next;
      p->next = c;
    }

  c->name = name;
  c->class = class;
  set_cmd_cfunc (c, fun);
  set_cmd_context (c, NULL);
  c->doc = doc;
  c->flags = 0;
  c->replacement = NULL;
  c->pre_show_hook = NULL;
  c->hook_pre  = NULL;
  c->hook_post = NULL;
  c->hook_in = 0;
  c->prefixlist = NULL;
  c->prefixname = NULL;
  c->allow_unknown = 0;
  c->abbrev_flag = 0;
  set_cmd_completer (c, make_symbol_completion_list);
  c->type = not_set_cmd;
  c->var = NULL;
  c->var_type = var_boolean;
  c->enums = NULL;
  c->user_commands = NULL;
  c->hookee_pre = NULL;
  c->hookee_post = NULL;
  c->cmd_pointer = NULL;

  return c;
}