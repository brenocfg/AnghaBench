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
 int /*<<< orphan*/  error (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
parse_binary_operation (char *arg)
{
  int length;

  if (!arg || !*arg)
    return 1;

  length = strlen (arg);

  while (arg[length - 1] == ' ' || arg[length - 1] == '\t')
    length--;

  if (strncmp (arg, "on", length) == 0
      || strncmp (arg, "1", length) == 0
      || strncmp (arg, "yes", length) == 0
      || strncmp (arg, "enable", length) == 0)
    return 1;
  else if (strncmp (arg, "off", length) == 0
	   || strncmp (arg, "0", length) == 0
	   || strncmp (arg, "no", length) == 0
	   || strncmp (arg, "disable", length) == 0)
    return 0;
  else
    {
      error ("\"on\" or \"off\" expected.");
      return 0;
    }
}