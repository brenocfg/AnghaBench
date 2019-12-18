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
struct ada_opname_map {char const* mangled; char const* demangled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_STREQN (char const*,char const*,int) ; 
 int /*<<< orphan*/  GROW_VECT (char*,size_t,int) ; 
 struct ada_opname_map* ada_opname_table ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

char *
ada_mangle (const char *demangled)
{
  static char *mangling_buffer = NULL;
  static size_t mangling_buffer_size = 0;
  const char *p;
  int k;

  if (demangled == NULL)
    return NULL;

  GROW_VECT (mangling_buffer, mangling_buffer_size,
	     2 * strlen (demangled) + 10);

  k = 0;
  for (p = demangled; *p != '\0'; p += 1)
    {
      if (*p == '.')
	{
	  mangling_buffer[k] = mangling_buffer[k + 1] = '_';
	  k += 2;
	}
      else if (*p == '"')
	{
	  const struct ada_opname_map *mapping;

	  for (mapping = ada_opname_table;
	       mapping->mangled != NULL &&
	       !DEPRECATED_STREQN (mapping->demangled, p, strlen (mapping->demangled));
	       p += 1)
	    ;
	  if (mapping->mangled == NULL)
	    error ("invalid Ada operator name: %s", p);
	  strcpy (mangling_buffer + k, mapping->mangled);
	  k += strlen (mapping->mangled);
	  break;
	}
      else
	{
	  mangling_buffer[k] = *p;
	  k += 1;
	}
    }

  mangling_buffer[k] = '\0';
  return mangling_buffer;
}