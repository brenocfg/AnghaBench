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
struct cmd_list_element {int flags; char* replacement; } ;

/* Variables and functions */
 int CMD_DEPRECATED ; 
 int DEPRECATED_WARN_USER ; 
 int MALLOCED_REPLACEMENT ; 
 int /*<<< orphan*/  lookup_cmd_composition (char*,struct cmd_list_element**,struct cmd_list_element**,struct cmd_list_element**) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
maintenance_do_deprecate (char *text, int deprecate)
{

  struct cmd_list_element *alias = NULL;
  struct cmd_list_element *prefix_cmd = NULL;
  struct cmd_list_element *cmd = NULL;

  char *start_ptr = NULL;
  char *end_ptr = NULL;
  int len;
  char *replacement = NULL;

  if (text == NULL)
    return;

  if (!lookup_cmd_composition (text, &alias, &prefix_cmd, &cmd))
    {
      printf_filtered ("Can't find command '%s' to deprecate.\n", text);
      return;
    }

  if (deprecate)
    {
      /* look for a replacement command */
      start_ptr = strchr (text, '\"');
      if (start_ptr != NULL)
	{
	  start_ptr++;
	  end_ptr = strrchr (start_ptr, '\"');
	  if (end_ptr != NULL)
	    {
	      len = end_ptr - start_ptr;
	      start_ptr[len] = '\0';
	      replacement = xstrdup (start_ptr);
	    }
	}
    }

  if (!start_ptr || !end_ptr)
    replacement = NULL;


  /* If they used an alias, we only want to deprecate the alias.

     Note the MALLOCED_REPLACEMENT test.  If the command's replacement
     string was allocated at compile time we don't want to free the
     memory. */
  if (alias)
    {

      if (alias->flags & MALLOCED_REPLACEMENT)
	xfree (alias->replacement);

      if (deprecate)
	alias->flags |= (DEPRECATED_WARN_USER | CMD_DEPRECATED);
      else
	alias->flags &= ~(DEPRECATED_WARN_USER | CMD_DEPRECATED);
      alias->replacement = replacement;
      alias->flags |= MALLOCED_REPLACEMENT;
      return;
    }
  else if (cmd)
    {
      if (cmd->flags & MALLOCED_REPLACEMENT)
	xfree (cmd->replacement);

      if (deprecate)
	cmd->flags |= (DEPRECATED_WARN_USER | CMD_DEPRECATED);
      else
	cmd->flags &= ~(DEPRECATED_WARN_USER | CMD_DEPRECATED);
      cmd->replacement = replacement;
      cmd->flags |= MALLOCED_REPLACEMENT;
      return;
    }
}