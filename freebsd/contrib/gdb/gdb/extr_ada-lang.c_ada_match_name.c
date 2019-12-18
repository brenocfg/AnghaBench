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
 scalar_t__ DEPRECATED_STREQN (char const*,char const*,int) ; 
 scalar_t__ is_name_suffix (char const*) ; 
 int strlen (char const*) ; 
 int wild_match (char const*,int,char const*) ; 

int
ada_match_name (const char *sym_name, const char *name, int wild)
{
  if (sym_name == NULL || name == NULL)
    return 0;
  else if (wild)
    return wild_match (name, strlen (name), sym_name);
  else
    {
      int len_name = strlen (name);
      return (DEPRECATED_STREQN (sym_name, name, len_name)
	      && is_name_suffix (sym_name + len_name))
	|| (DEPRECATED_STREQN (sym_name, "_ada_", 5)
	    && DEPRECATED_STREQN (sym_name + 5, name, len_name)
	    && is_name_suffix (sym_name + len_name + 5));
    }
}