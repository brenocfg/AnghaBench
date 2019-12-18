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
struct cmd_list_element {int /*<<< orphan*/  var; int /*<<< orphan*/  var_type; int /*<<< orphan*/  class; int /*<<< orphan*/  name; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  setstring ;

/* Variables and functions */
 struct cmd_list_element* add_set_or_show_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**) ; 
 char* concat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  show_cmd ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

struct cmd_list_element *
add_show_from_set (struct cmd_list_element *setcmd,
		   struct cmd_list_element **list)
{
  char *doc;
  const static char setstring[] = "Set ";

  /* Create a doc string by replacing "Set " at the start of the
     `set'' command's doco with "Show ".  */
  gdb_assert (strncmp (setcmd->doc, setstring, sizeof (setstring) - 1) == 0);
  doc = concat ("Show ", setcmd->doc + sizeof (setstring) - 1, NULL);

  /* Insert the basic command.  */
  return add_set_or_show_cmd (setcmd->name, show_cmd, setcmd->class,
			      setcmd->var_type, setcmd->var, doc, list);
}