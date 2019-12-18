#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ search_arch_type ;

/* Variables and functions */
 char TOLOWER (char) ; 
 char const* ldfile_output_machine_name ; 
 TYPE_1__** search_arch_tail_ptr ; 
 TYPE_1__* xmalloc (int) ; 
 char* xstrdup (char const*) ; 

void
ldfile_add_arch (const char *in_name)
{
  char *name = xstrdup (in_name);
  search_arch_type *new = xmalloc (sizeof (search_arch_type));

  ldfile_output_machine_name = in_name;

  new->name = name;
  new->next = NULL;
  while (*name)
    {
      *name = TOLOWER (*name);
      name++;
    }
  *search_arch_tail_ptr = new;
  search_arch_tail_ptr = &new->next;

}