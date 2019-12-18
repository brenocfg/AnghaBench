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
struct cmd_list_element {int flags; struct cmd_list_element** prefixlist; struct cmd_list_element* cmd_pointer; } ;

/* Variables and functions */
 int DEPRECATED_WARN_USER ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  deprecated_cmd_warning (char**) ; 
 struct cmd_list_element* find_cmd (char*,int,struct cmd_list_element*,int,int*) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isupper (char) ; 
 char tolower (char) ; 
 scalar_t__ tui_active ; 
 scalar_t__ xdb_commands ; 

struct cmd_list_element *
lookup_cmd_1 (char **text, struct cmd_list_element *clist,
	      struct cmd_list_element **result_list, int ignore_help_classes)
{
  char *p, *command;
  int len, tmp, nfound;
  struct cmd_list_element *found, *c;
  char *line = *text;

  while (**text == ' ' || **text == '\t')
    (*text)++;

  /* Treating underscores as part of command words is important
     so that "set args_foo()" doesn't get interpreted as
     "set args _foo()".  */
  /* NOTE: cagney/2003-02-13 The `tui_active' was previously
     `tui_version'.  */
  for (p = *text;
       *p && (isalnum (*p) || *p == '-' || *p == '_' ||
#if defined(TUI)
	      (tui_active &&
	       (*p == '+' || *p == '<' || *p == '>' || *p == '$')) ||
#endif
	      (xdb_commands && (*p == '!' || *p == '/' || *p == '?')));
       p++)
    ;

  /* If nothing but whitespace, return 0.  */
  if (p == *text)
    return 0;

  len = p - *text;

  /* *text and p now bracket the first command word to lookup (and
     it's length is len).  We copy this into a local temporary */


  command = (char *) alloca (len + 1);
  for (tmp = 0; tmp < len; tmp++)
    {
      char x = (*text)[tmp];
      command[tmp] = x;
    }
  command[len] = '\0';

  /* Look it up.  */
  found = 0;
  nfound = 0;
  found = find_cmd (command, len, clist, ignore_help_classes, &nfound);

  /* 
     ** We didn't find the command in the entered case, so lower case it
     ** and search again.
   */
  if (!found || nfound == 0)
    {
      for (tmp = 0; tmp < len; tmp++)
	{
	  char x = command[tmp];
	  command[tmp] = isupper (x) ? tolower (x) : x;
	}
      found = find_cmd (command, len, clist, ignore_help_classes, &nfound);
    }

  /* If nothing matches, we have a simple failure.  */
  if (nfound == 0)
    return 0;

  if (nfound > 1)
    {
      if (result_list != NULL)
	/* Will be modified in calling routine
	   if we know what the prefix command is.  */
	*result_list = 0;
      return (struct cmd_list_element *) -1;	/* Ambiguous.  */
    }

  /* We've matched something on this list.  Move text pointer forward. */

  *text = p;

  if (found->cmd_pointer)
    {
      /* We drop the alias (abbreviation) in favor of the command it is
       pointing to.  If the alias is deprecated, though, we need to
       warn the user about it before we drop it.  Note that while we
       are warning about the alias, we may also warn about the command
       itself and we will adjust the appropriate DEPRECATED_WARN_USER
       flags */
      
      if (found->flags & DEPRECATED_WARN_USER)
      deprecated_cmd_warning (&line);
      found = found->cmd_pointer;
    }
  /* If we found a prefix command, keep looking.  */

  if (found->prefixlist)
    {
      c = lookup_cmd_1 (text, *found->prefixlist, result_list,
			ignore_help_classes);
      if (!c)
	{
	  /* Didn't find anything; this is as far as we got.  */
	  if (result_list != NULL)
	    *result_list = clist;
	  return found;
	}
      else if (c == (struct cmd_list_element *) -1)
	{
	  /* We've gotten this far properly, but the next step
	     is ambiguous.  We need to set the result list to the best
	     we've found (if an inferior hasn't already set it).  */
	  if (result_list != NULL)
	    if (!*result_list)
	      /* This used to say *result_list = *found->prefixlist
	         If that was correct, need to modify the documentation
	         at the top of this function to clarify what is supposed
	         to be going on.  */
	      *result_list = found;
	  return c;
	}
      else
	{
	  /* We matched!  */
	  return c;
	}
    }
  else
    {
      if (result_list != NULL)
	*result_list = clist;
      return found;
    }
}