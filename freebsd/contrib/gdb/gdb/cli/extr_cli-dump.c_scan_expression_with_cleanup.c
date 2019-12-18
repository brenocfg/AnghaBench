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
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 char* savestring (char*,int) ; 
 char* skip_spaces (char*) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char const*) ; 

char *
scan_expression_with_cleanup (char **cmd, const char *def)
{
  if ((*cmd) == NULL || (**cmd) == '\0')
    {
      char *exp = xstrdup (def);
      make_cleanup (xfree, exp);
      return exp;
    }
  else
    {
      char *exp;
      char *end;

      end = (*cmd) + strcspn (*cmd, " \t");
      exp = savestring ((*cmd), end - (*cmd));
      make_cleanup (xfree, exp);
      (*cmd) = skip_spaces (end);
      return exp;
    }
}