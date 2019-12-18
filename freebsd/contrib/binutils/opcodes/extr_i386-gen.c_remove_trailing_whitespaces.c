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
 scalar_t__ ISSPACE (char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
remove_trailing_whitespaces (char *str)
{
  size_t last = strlen (str);

  if (last == 0)
    return;

  do
    {
      last--;
      if (ISSPACE (str [last]))
	str[last] = '\0';
      else
	break;
    }
  while (last != 0);
}