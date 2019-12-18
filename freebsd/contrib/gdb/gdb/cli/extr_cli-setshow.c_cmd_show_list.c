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
struct cmd_list_element {char* prefixname; scalar_t__ type; char* name; struct cmd_list_element** prefixlist; int /*<<< orphan*/  abbrev_flag; struct cmd_list_element* next; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_setshow_command (char*,int,struct cmd_list_element*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ show_cmd ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

void
cmd_show_list (struct cmd_list_element *list, int from_tty, char *prefix)
{
  struct cleanup *showlist_chain;

  showlist_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "showlist");
  for (; list != NULL; list = list->next)
    {
      /* If we find a prefix, run its list, prefixing our output by its
         prefix (with "show " skipped).  */
      if (list->prefixlist && !list->abbrev_flag)
	{
	  struct cleanup *optionlist_chain
	    = make_cleanup_ui_out_tuple_begin_end (uiout, "optionlist");
	  ui_out_field_string (uiout, "prefix", list->prefixname + 5);
	  cmd_show_list (*list->prefixlist, from_tty, list->prefixname + 5);
	  /* Close the tuple.  */
	  do_cleanups (optionlist_chain);
	}
      if (list->type == show_cmd)
	{
	  struct cleanup *option_chain
	    = make_cleanup_ui_out_tuple_begin_end (uiout, "option");
	  ui_out_text (uiout, prefix);
	  ui_out_field_string (uiout, "name", list->name);
	  ui_out_text (uiout, ":  ");
	  do_setshow_command ((char *) NULL, from_tty, list);
          /* Close the tuple.  */
	  do_cleanups (option_chain);
	}
    }
  /* Close the tuple.  */
  do_cleanups (showlist_chain);
}