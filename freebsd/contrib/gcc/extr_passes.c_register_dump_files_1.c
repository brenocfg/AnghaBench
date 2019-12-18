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
struct tree_opt_pass {int properties_provided; int properties_destroyed; struct tree_opt_pass* next; scalar_t__ gate; struct tree_opt_pass* sub; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_one_dump_file (struct tree_opt_pass*,int,int) ; 

__attribute__((used)) static int 
register_dump_files_1 (struct tree_opt_pass *pass, bool ipa, int properties)
{
  do
    {
      int new_properties = (properties | pass->properties_provided)
			   & ~pass->properties_destroyed;

      if (pass->name)
        register_one_dump_file (pass, ipa, new_properties);

      if (pass->sub)
        new_properties = register_dump_files_1 (pass->sub, false,
						new_properties);

      /* If we have a gate, combine the properties that we could have with
         and without the pass being examined.  */
      if (pass->gate)
        properties &= new_properties;
      else
        properties = new_properties;

      pass = pass->next;
    }
  while (pass);

  return properties;
}