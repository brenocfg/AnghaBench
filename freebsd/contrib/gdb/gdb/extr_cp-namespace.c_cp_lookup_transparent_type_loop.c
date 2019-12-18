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
struct type {int dummy; } ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 struct type* basic_lookup_transparent_type (char*) ; 
 int cp_find_first_component (char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static struct type *
cp_lookup_transparent_type_loop (const char *name, const char *scope,
				 int length)
{
  int scope_length = length + cp_find_first_component (scope + length);
  char *full_name;

  /* If the current scope is followed by "::", look in the next
     component.  */
  if (scope[scope_length] == ':')
    {
      struct type *retval
	= cp_lookup_transparent_type_loop (name, scope, scope_length + 2);
      if (retval != NULL)
	return retval;
    }

  full_name = alloca (scope_length + 2 + strlen (name) + 1);
  strncpy (full_name, scope, scope_length);
  strncpy (full_name + scope_length, "::", 2);
  strcpy (full_name + scope_length + 2, name);

  return basic_lookup_transparent_type (full_name);
}