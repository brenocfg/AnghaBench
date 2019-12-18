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
struct using_direct {char* inner; int /*<<< orphan*/  outer; struct using_direct* next; } ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 struct using_direct* block_using (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_symbol_overload_list_qualified (char const*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
make_symbol_overload_list_using (const char *func_name,
				 const char *namespace)
{
  const struct using_direct *current;

  /* First, go through the using directives.  If any of them apply,
     look in the appropriate namespaces for new functions to match
     on.  */

  for (current = block_using (get_selected_block (0));
       current != NULL;
       current = current->next)
    {
      if (strcmp (namespace, current->outer) == 0)
	{
	  make_symbol_overload_list_using (func_name,
					   current->inner);
	}
    }

  /* Now, add names for this namespace.  */
  
  if (namespace[0] == '\0')
    {
      make_symbol_overload_list_qualified (func_name);
    }
  else
    {
      char *concatenated_name
	= alloca (strlen (namespace) + 2 + strlen (func_name) + 1);
      strcpy (concatenated_name, namespace);
      strcat (concatenated_name, "::");
      strcat (concatenated_name, func_name);
      make_symbol_overload_list_qualified (concatenated_name);
    }
}