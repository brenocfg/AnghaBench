#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct spu_link_hash_table {int dummy; } ;
struct spu_elf_stack_info {int num_fun; TYPE_4__* fun; } ;
struct call_info {struct call_info* next; } ;
struct bfd_link_info {TYPE_1__* input_bfds; } ;
struct _spu_elf_section_data {struct spu_elf_stack_info* stack_info; } ;
typedef  int /*<<< orphan*/  bfd_target ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {TYPE_2__* sections; int /*<<< orphan*/  const* xvec; struct TYPE_10__* link_next; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_11__ {scalar_t__ reloc_count; struct TYPE_11__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_12__ {int /*<<< orphan*/  non_root; int /*<<< orphan*/  visit1; struct call_info* call_list; int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  call_graph_traverse (TYPE_4__*,struct bfd_link_info*) ; 
 int /*<<< orphan*/  free (struct call_info*) ; 
 int /*<<< orphan*/  insert_callee (int /*<<< orphan*/ *,struct call_info*) ; 
 int /*<<< orphan*/  interesting_section (TYPE_2__*,TYPE_1__*,struct spu_link_hash_table*) ; 
 int /*<<< orphan*/  mark_functions_via_relocs (TYPE_2__*,struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_non_root (TYPE_4__*) ; 
 struct _spu_elf_section_data* spu_elf_section_data (TYPE_2__*) ; 
 struct spu_link_hash_table* spu_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
build_call_tree (bfd *output_bfd, struct bfd_link_info *info)
{
  struct spu_link_hash_table *htab = spu_hash_table (info);
  bfd *ibfd;

  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      extern const bfd_target bfd_elf32_spu_vec;
      asection *sec;

      if (ibfd->xvec != &bfd_elf32_spu_vec)
	continue;

      for (sec = ibfd->sections; sec != NULL; sec = sec->next)
	{
	  if (!interesting_section (sec, output_bfd, htab)
	      || sec->reloc_count == 0)
	    continue;

	  if (!mark_functions_via_relocs (sec, info, TRUE))
	    return FALSE;
	}

      /* Transfer call info from hot/cold section part of function
	 to main entry.  */
      for (sec = ibfd->sections; sec != NULL; sec = sec->next)
	{
	  struct _spu_elf_section_data *sec_data;
	  struct spu_elf_stack_info *sinfo;

	  if ((sec_data = spu_elf_section_data (sec)) != NULL
	      && (sinfo = sec_data->stack_info) != NULL)
	    {
	      int i;
	      for (i = 0; i < sinfo->num_fun; ++i)
		{
		  if (sinfo->fun[i].start != NULL)
		    {
		      struct call_info *call = sinfo->fun[i].call_list;

		      while (call != NULL)
			{
			  struct call_info *call_next = call->next;
			  if (!insert_callee (sinfo->fun[i].start, call))
			    free (call);
			  call = call_next;
			}
		      sinfo->fun[i].call_list = NULL;
		      sinfo->fun[i].non_root = TRUE;
		    }
		}
	    }
	}
    }

  /* Find the call graph root(s).  */
  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      extern const bfd_target bfd_elf32_spu_vec;
      asection *sec;

      if (ibfd->xvec != &bfd_elf32_spu_vec)
	continue;

      for (sec = ibfd->sections; sec != NULL; sec = sec->next)
	{
	  struct _spu_elf_section_data *sec_data;
	  struct spu_elf_stack_info *sinfo;

	  if ((sec_data = spu_elf_section_data (sec)) != NULL
	      && (sinfo = sec_data->stack_info) != NULL)
	    {
	      int i;
	      for (i = 0; i < sinfo->num_fun; ++i)
		if (!sinfo->fun[i].visit1)
		  mark_non_root (&sinfo->fun[i]);
	    }
	}
    }

  /* Remove cycles from the call graph.  We start from the root node(s)
     so that we break cycles in a reasonable place.  */
  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      extern const bfd_target bfd_elf32_spu_vec;
      asection *sec;

      if (ibfd->xvec != &bfd_elf32_spu_vec)
	continue;

      for (sec = ibfd->sections; sec != NULL; sec = sec->next)
	{
	  struct _spu_elf_section_data *sec_data;
	  struct spu_elf_stack_info *sinfo;

	  if ((sec_data = spu_elf_section_data (sec)) != NULL
	      && (sinfo = sec_data->stack_info) != NULL)
	    {
	      int i;
	      for (i = 0; i < sinfo->num_fun; ++i)
		if (!sinfo->fun[i].non_root)
		  call_graph_traverse (&sinfo->fun[i], info);
	    }
	}
    }

  return TRUE;
}