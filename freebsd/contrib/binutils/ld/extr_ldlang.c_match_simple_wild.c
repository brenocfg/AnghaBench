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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
match_simple_wild (const char *pattern, const char *name)
{
  /* The first four characters of the pattern are guaranteed valid
     non-wildcard characters.  So we can go faster.  */
  if (pattern[0] != name[0] || pattern[1] != name[1]
      || pattern[2] != name[2] || pattern[3] != name[3])
    return FALSE;

  pattern += 4;
  name += 4;
  while (*pattern != '*')
    if (*name++ != *pattern++)
      return FALSE;

  return TRUE;
}