#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct spu_elf_stack_info {int num_fun; struct function_info* fun; } ;
struct function_info {struct function_info* start; } ;
struct TYPE_17__ {TYPE_6__* section; } ;
struct TYPE_18__ {TYPE_3__ indirect; } ;
struct bfd_link_order {scalar_t__ type; TYPE_4__ u; struct bfd_link_order* next; } ;
struct bfd_link_info {TYPE_5__* callbacks; } ;
struct _spu_elf_section_data {struct spu_elf_stack_info* stack_info; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_20__ {TYPE_2__* output_section; int /*<<< orphan*/  owner; int /*<<< orphan*/  size; } ;
typedef  TYPE_6__ asection ;
struct TYPE_21__ {int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_size; scalar_t__ st_value; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* einfo ) (int /*<<< orphan*/ ,TYPE_6__*) ;} ;
struct TYPE_15__ {struct bfd_link_order* link_order; } ;
struct TYPE_16__ {TYPE_1__ map_head; } ;
typedef  TYPE_7__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_section_from_bfd_section (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ bfd_indirect_link_order ; 
 TYPE_7__* bfd_zmalloc (int) ; 
 struct function_info* maybe_insert_function (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _spu_elf_section_data* spu_elf_section_data (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static bfd_boolean
pasted_function (asection *sec, struct bfd_link_info *info)
{
  struct bfd_link_order *l;
  struct _spu_elf_section_data *sec_data;
  struct spu_elf_stack_info *sinfo;
  Elf_Internal_Sym *fake;
  struct function_info *fun, *fun_start;

  fake = bfd_zmalloc (sizeof (*fake));
  if (fake == NULL)
    return FALSE;
  fake->st_value = 0;
  fake->st_size = sec->size;
  fake->st_shndx
    = _bfd_elf_section_from_bfd_section (sec->owner, sec);
  fun = maybe_insert_function (sec, fake, FALSE, FALSE);
  if (!fun)
    return FALSE;

  /* Find a function immediately preceding this section.  */
  fun_start = NULL;
  for (l = sec->output_section->map_head.link_order; l != NULL; l = l->next)
    {
      if (l->u.indirect.section == sec)
	{
	  if (fun_start != NULL)
	    {
	      if (fun_start->start)
		fun_start = fun_start->start;
	      fun->start = fun_start;
	    }
	  return TRUE;
	}
      if (l->type == bfd_indirect_link_order
	  && (sec_data = spu_elf_section_data (l->u.indirect.section)) != NULL
	  && (sinfo = sec_data->stack_info) != NULL
	  && sinfo->num_fun != 0)
	fun_start = &sinfo->fun[sinfo->num_fun - 1];
    }

  info->callbacks->einfo (_("%A link_order not found\n"), sec);
  return FALSE;
}