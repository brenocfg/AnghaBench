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
struct command_line {char* line; struct command_line* next; } ;
struct cmd_list_element {scalar_t__ class; char* doc; } ;

/* Variables and functions */
 scalar_t__ class_user ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  free_command_lines (struct command_line**) ; 
 struct cmd_list_element* lookup_cmd (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct command_line* read_command_lines (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  validate_comname (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

void
document_command (char *comname, int from_tty)
{
  struct command_line *doclines;
  struct cmd_list_element *c;
  char *tem = comname;
  char tmpbuf[128];

  validate_comname (comname);

  c = lookup_cmd (&tem, cmdlist, "", 0, 1);

  if (c->class != class_user)
    error ("Command \"%s\" is built-in.", comname);

  sprintf (tmpbuf, "Type documentation for \"%s\".", comname);
  doclines = read_command_lines (tmpbuf, from_tty);

  if (c->doc)
    xfree (c->doc);

  {
    struct command_line *cl1;
    int len = 0;

    for (cl1 = doclines; cl1; cl1 = cl1->next)
      len += strlen (cl1->line) + 1;

    c->doc = (char *) xmalloc (len + 1);
    *c->doc = 0;

    for (cl1 = doclines; cl1; cl1 = cl1->next)
      {
	strcat (c->doc, cl1->line);
	if (cl1->next)
	  strcat (c->doc, "\n");
      }
  }

  free_command_lines (&doclines);
}