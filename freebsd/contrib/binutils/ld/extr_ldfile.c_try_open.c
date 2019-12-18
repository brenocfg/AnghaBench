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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  info_msg (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ trace_file_tries ; 

__attribute__((used)) static FILE *
try_open (const char *name, const char *exten)
{
  FILE *result;
  char buff[1000];

  result = fopen (name, "r");

  if (trace_file_tries)
    {
      if (result == NULL)
	info_msg (_("cannot find script file %s\n"), name);
      else
	info_msg (_("opened script file %s\n"), name);
    }

  if (result != NULL)
    return result;

  if (*exten)
    {
      sprintf (buff, "%s%s", name, exten);
      result = fopen (buff, "r");

      if (trace_file_tries)
	{
	  if (result == NULL)
	    info_msg (_("cannot find script file %s\n"), buff);
	  else
	    info_msg (_("opened script file %s\n"), buff);
	}
    }

  return result;
}