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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 char const EOS ; 
 scalar_t__ ISSPACE (char) ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ *) ; 

int
writeargv (char **argv, FILE *f)
{
  int status = 0;

  if (f == NULL)
    return 1;

  while (*argv != NULL)
    {
      const char *arg = *argv;

      while (*arg != EOS)
        {
          char c = *arg;

          if (ISSPACE(c) || c == '\\' || c == '\'' || c == '"')
            if (EOF == fputc ('\\', f))
              {
                status = 1;
                goto done;
              }

          if (EOF == fputc (c, f))
            {
              status = 1;
              goto done;
            }
          arg++;
        }

      if (EOF == fputc ('\n', f))
        {
          status = 1;
          goto done;
        }
      argv++;
    }

 done:
  return status;
}