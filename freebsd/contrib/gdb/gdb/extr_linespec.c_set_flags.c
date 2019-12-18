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

/* Variables and functions */
 char* get_gdb_completer_quote_characters () ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
set_flags (char *arg, int *is_quoted, char **paren_pointer)
{
  char *ii;
  int has_if = 0;

  /* 'has_if' is for the syntax:
        (gdb) break foo if (a==b)
  */
  if ((ii = strstr (arg, " if ")) != NULL ||
      (ii = strstr (arg, "\tif ")) != NULL ||
      (ii = strstr (arg, " if\t")) != NULL ||
      (ii = strstr (arg, "\tif\t")) != NULL ||
      (ii = strstr (arg, " if(")) != NULL ||
      (ii = strstr (arg, "\tif( ")) != NULL)
    has_if = 1;
  /* Temporarily zap out "if (condition)" to not confuse the
     parenthesis-checking code below.  This is undone below. Do not
     change ii!!  */
  if (has_if)
    {
      *ii = '\0';
    }

  *is_quoted = (*arg
		&& strchr (get_gdb_completer_quote_characters (),
			   *arg) != NULL);

  *paren_pointer = strchr (arg, '(');
  if (*paren_pointer != NULL)
    *paren_pointer = strrchr (*paren_pointer, ')');

  /* Now that we're safely past the paren_pointer check, put back " if
     (condition)" so outer layers can see it.  */
  if (has_if)
    *ii = ' ';
}