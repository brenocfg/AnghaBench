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
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 scalar_t__ ISSPACE (char const) ; 
 int /*<<< orphan*/  fatal_with_file_and_line (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void
validate_const_int (FILE *infile, const char *string)
{
  const char *cp;
  int valid = 1;

  cp = string;
  while (*cp && ISSPACE (*cp))
    cp++;
  if (*cp == '-' || *cp == '+')
    cp++;
  if (*cp == 0)
    valid = 0;
  for (; *cp; cp++)
    if (! ISDIGIT (*cp))
      valid = 0;
  if (!valid)
    fatal_with_file_and_line (infile, "invalid decimal constant \"%s\"\n", string);
}