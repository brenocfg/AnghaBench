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
 int /*<<< orphan*/  CONSTRAINT_LEN (int,char const*) ; 
 scalar_t__ EXTRA_MEMORY_CONSTRAINT (int,char const*) ; 

__attribute__((used)) static int
alternative_allows_memconst (const char *constraint, int altnum)
{
  int c;
  /* Skip alternatives before the one requested.  */
  while (altnum > 0)
    {
      while (*constraint++ != ',');
      altnum--;
    }
  /* Scan the requested alternative for 'm' or 'o'.
     If one of them is present, this alternative accepts memory constants.  */
  for (; (c = *constraint) && c != ',' && c != '#';
       constraint += CONSTRAINT_LEN (c, constraint))
    if (c == 'm' || c == 'o' || EXTRA_MEMORY_CONSTRAINT (c, constraint))
      return 1;
  return 0;
}