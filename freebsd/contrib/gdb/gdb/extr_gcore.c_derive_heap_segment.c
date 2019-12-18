#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ value ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_11__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_12__ {struct TYPE_12__* next; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int SEC_DATA ; 
 int bfd_get_section_flags (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ bfd_get_section_size (TYPE_2__*) ; 
 scalar_t__ bfd_get_section_vma (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_section_name (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 scalar_t__* call_function_by_hand (scalar_t__*,int,scalar_t__**) ; 
 scalar_t__* find_function_in_inferior (char*) ; 
 int /*<<< orphan*/  gdb_assert (scalar_t__*) ; 
 int /*<<< orphan*/ * lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_execution ; 
 scalar_t__ value_as_long (scalar_t__*) ; 
 scalar_t__* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
derive_heap_segment (bfd *abfd, bfd_vma *bottom, bfd_vma *top)
{
  bfd_vma top_of_data_memory = 0;
  bfd_vma top_of_heap = 0;
  bfd_size_type sec_size;
  struct value *zero, *sbrk;
  bfd_vma sec_vaddr;
  asection *sec;

  gdb_assert (bottom);
  gdb_assert (top);

  /* This function depends on being able to call a function in the
     inferior.  */
  if (!target_has_execution)
    return 0;

  /* The following code assumes that the link map is arranged as
     follows (low to high addresses):

     ---------------------------------
     | text sections                 |
     ---------------------------------
     | data sections (including bss) |
     ---------------------------------
     | heap                          |
     --------------------------------- */

  for (sec = abfd->sections; sec; sec = sec->next)
    {
      if (bfd_get_section_flags (abfd, sec) & SEC_DATA
	  || strcmp (".bss", bfd_section_name (abfd, sec)) == 0)
	{
	  sec_vaddr = bfd_get_section_vma (abfd, sec);
	  sec_size = bfd_get_section_size (sec);
	  if (sec_vaddr + sec_size > top_of_data_memory)
	    top_of_data_memory = sec_vaddr + sec_size;
	}
    }

  /* Now get the top-of-heap by calling sbrk in the inferior.  */
  if (lookup_minimal_symbol ("sbrk", NULL, NULL) != NULL)
    {
      sbrk = find_function_in_inferior ("sbrk");
      if (sbrk == NULL)
	return 0;
    }
  else if (lookup_minimal_symbol ("_sbrk", NULL, NULL) != NULL)
    {
      sbrk = find_function_in_inferior ("_sbrk");
      if (sbrk == NULL)
	return 0;
    }
  else
    return 0;

  zero = value_from_longest (builtin_type_int, 0);
  gdb_assert (zero);
  sbrk = call_function_by_hand (sbrk, 1, &zero);
  if (sbrk == NULL)
    return 0;
  top_of_heap = value_as_long (sbrk);

  /* Return results.  */
  if (top_of_heap > top_of_data_memory)
    {
      *bottom = top_of_data_memory;
      *top = top_of_heap;
      return 1;
    }

  /* No additional heap space needs to be saved.  */
  return 0;
}