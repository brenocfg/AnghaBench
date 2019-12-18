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
 int /*<<< orphan*/  ISDIGIT (unsigned char) ; 
 int consume_count (char const**) ; 

__attribute__((used)) static int
consume_count_with_underscores (const char **mangled)
{
  int idx;

  if (**mangled == '_')
    {
      (*mangled)++;
      if (!ISDIGIT ((unsigned char)**mangled))
	return -1;

      idx = consume_count (mangled);
      if (**mangled != '_')
	/* The trailing underscore was missing. */
	return -1;

      (*mangled)++;
    }
  else
    {
      if (**mangled < '0' || **mangled > '9')
	return -1;

      idx = **mangled - '0';
      (*mangled)++;
    }

  return idx;
}