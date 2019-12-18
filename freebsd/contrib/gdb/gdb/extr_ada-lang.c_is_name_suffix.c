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
 scalar_t__ DEPRECATED_STREQ (char const*,char*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 

__attribute__((used)) static int
is_name_suffix (const char *str)
{
  int k;
  if (str[0] == 'X')
    {
      str += 1;
      while (str[0] != '_' && str[0] != '\0')
	{
	  if (str[0] != 'n' && str[0] != 'b')
	    return 0;
	  str += 1;
	}
    }
  if (str[0] == '\000')
    return 1;
  if (str[0] == '_')
    {
      if (str[1] != '_' || str[2] == '\000')
	return 0;
      if (str[2] == '_')
	{
	  if (DEPRECATED_STREQ (str + 3, "LJM"))
	    return 1;
	  if (str[3] != 'X')
	    return 0;
	  if (str[4] == 'F' || str[4] == 'D' || str[4] == 'B' ||
	      str[4] == 'U' || str[4] == 'P')
	    return 1;
	  if (str[4] == 'R' && str[5] != 'T')
	    return 1;
	  return 0;
	}
      for (k = 2; str[k] != '\0'; k += 1)
	if (!isdigit (str[k]))
	  return 0;
      return 1;
    }
  if (str[0] == '$' && str[1] != '\000')
    {
      for (k = 1; str[k] != '\0'; k += 1)
	if (!isdigit (str[k]))
	  return 0;
      return 1;
    }
  return 0;
}