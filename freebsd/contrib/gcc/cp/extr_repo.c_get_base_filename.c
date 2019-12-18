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
 char* extract_string (char**) ; 
 scalar_t__ flag_use_repository ; 
 char* getenv (char*) ; 
 char const* lbasename (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *
get_base_filename (const char *filename)
{
  char *p = getenv ("COLLECT_GCC_OPTIONS");
  char *output = NULL;
  int compiling = 0;

  while (p && *p)
    {
      char *q = extract_string (&p);

      if (strcmp (q, "-o") == 0)
	output = extract_string (&p);
      else if (strcmp (q, "-c") == 0)
	compiling = 1;
    }

  if (compiling && output)
    return output;

  if (p && ! compiling)
    {
      warning (0, "-frepo must be used with -c");
      flag_use_repository = 0;
      return NULL;
    }

  return lbasename (filename);
}