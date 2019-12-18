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

__attribute__((used)) static int
specialcmp (char *a, char *b)
{
  while (*a && *a != ' ' && *a != ']' && *b && *b != ' ' && *b != ']')
    {
      if (*a != *b)
	return *a - *b;
      a++, b++;
    }
  if (*a && *a != ' ' && *a != ']')
    return  1;		/* a is longer therefore greater */
  if (*b && *b != ' ' && *b != ']')
    return -1;		/* a is shorter therefore lesser */
  return    0;		/* a and b are identical */
}