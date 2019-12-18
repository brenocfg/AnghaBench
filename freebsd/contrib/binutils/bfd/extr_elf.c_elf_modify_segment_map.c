#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_segment_map {unsigned int count; scalar_t__ p_type; struct elf_segment_map* next; TYPE_1__** sections; } ;
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_modify_segment_map ) (int /*<<< orphan*/ *,struct bfd_link_info*) ;} ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {struct elf_segment_map* segment_map; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PT_LOAD ; 
 int SEC_ALLOC ; 
 int SEC_EXCLUDE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
elf_modify_segment_map (bfd *abfd, struct bfd_link_info *info)
{
  struct elf_segment_map **m;
  const struct elf_backend_data *bed;

  /* The placement algorithm assumes that non allocated sections are
     not in PT_LOAD segments.  We ensure this here by removing such
     sections from the segment map.  We also remove excluded
     sections.  Finally, any PT_LOAD segment without sections is
     removed.  */
  m = &elf_tdata (abfd)->segment_map;
  while (*m)
    {
      unsigned int i, new_count;

      for (new_count = 0, i = 0; i < (*m)->count; i++)
	{
	  if (((*m)->sections[i]->flags & SEC_EXCLUDE) == 0
	      && (((*m)->sections[i]->flags & SEC_ALLOC) != 0
		  || (*m)->p_type != PT_LOAD))
	    {
	      (*m)->sections[new_count] = (*m)->sections[i];
	      new_count++;
	    }
	}
      (*m)->count = new_count;

      if ((*m)->p_type == PT_LOAD && (*m)->count == 0)
	*m = (*m)->next;
      else
	m = &(*m)->next;
    }

  bed = get_elf_backend_data (abfd);
  if (bed->elf_backend_modify_segment_map != NULL)
    {
      if (!(*bed->elf_backend_modify_segment_map) (abfd, info))
	return FALSE;
    }

  return TRUE;
}