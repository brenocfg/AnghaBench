#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_size_type ;
struct TYPE_3__ {char* printable_name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 TYPE_1__** bfd_archures_list ; 
 char** bfd_malloc (int) ; 

const char **
bfd_arch_list (void)
{
  int vec_length = 0;
  const char **name_ptr;
  const char **name_list;
  const bfd_arch_info_type * const *app;
  bfd_size_type amt;

  /* Determine the number of architectures.  */
  vec_length = 0;
  for (app = bfd_archures_list; *app != NULL; app++)
    {
      const bfd_arch_info_type *ap;
      for (ap = *app; ap != NULL; ap = ap->next)
	{
	  vec_length++;
	}
    }

  amt = (vec_length + 1) * sizeof (char **);
  name_list = bfd_malloc (amt);
  if (name_list == NULL)
    return NULL;

  /* Point the list at each of the names.  */
  name_ptr = name_list;
  for (app = bfd_archures_list; *app != NULL; app++)
    {
      const bfd_arch_info_type *ap;
      for (ap = *app; ap != NULL; ap = ap->next)
	{
	  *name_ptr = ap->printable_name;
	  name_ptr++;
	}
    }
  *name_ptr = NULL;

  return name_list;
}