#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spu_elf_stack_info {int num_fun; int max_fun; struct function_info* fun; } ;
struct TYPE_9__ {void* sym; void* h; } ;
struct function_info {scalar_t__ lo; scalar_t__ hi; int /*<<< orphan*/  stack; TYPE_4__ u; int /*<<< orphan*/ * sec; void* global; void* is_func; } ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_7__ {TYPE_1__ def; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct elf_link_hash_entry {scalar_t__ size; TYPE_3__ root; } ;
struct _spu_elf_section_data {struct spu_elf_stack_info* stack_info; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  void* bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_10__ {scalar_t__ st_value; scalar_t__ st_size; } ;
typedef  TYPE_5__ Elf_Internal_Sym ;

/* Variables and functions */
 void* TRUE ; 
 struct spu_elf_stack_info* alloc_stack_info (int /*<<< orphan*/ *,int) ; 
 struct spu_elf_stack_info* bfd_realloc (struct spu_elf_stack_info*,int) ; 
 int /*<<< orphan*/  find_function_stack_adjust (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memmove (struct function_info*,struct function_info*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct _spu_elf_section_data* spu_elf_section_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct function_info *
maybe_insert_function (asection *sec,
		       void *sym_h,
		       bfd_boolean global,
		       bfd_boolean is_func)
{
  struct _spu_elf_section_data *sec_data = spu_elf_section_data (sec);
  struct spu_elf_stack_info *sinfo = sec_data->stack_info;
  int i;
  bfd_vma off, size;

  if (sinfo == NULL)
    {
      sinfo = alloc_stack_info (sec, 20);
      if (sinfo == NULL)
	return NULL;
    }

  if (!global)
    {
      Elf_Internal_Sym *sym = sym_h;
      off = sym->st_value;
      size = sym->st_size;
    }
  else
    {
      struct elf_link_hash_entry *h = sym_h;
      off = h->root.u.def.value;
      size = h->size;
    }

  for (i = sinfo->num_fun; --i >= 0; )
    if (sinfo->fun[i].lo <= off)
      break;

  if (i >= 0)
    {
      /* Don't add another entry for an alias, but do update some
	 info.  */
      if (sinfo->fun[i].lo == off)
	{
	  /* Prefer globals over local syms.  */
	  if (global && !sinfo->fun[i].global)
	    {
	      sinfo->fun[i].global = TRUE;
	      sinfo->fun[i].u.h = sym_h;
	    }
	  if (is_func)
	    sinfo->fun[i].is_func = TRUE;
	  return &sinfo->fun[i];
	}
      /* Ignore a zero-size symbol inside an existing function.  */
      else if (sinfo->fun[i].hi > off && size == 0)
	return &sinfo->fun[i];
    }

  if (++i < sinfo->num_fun)
    memmove (&sinfo->fun[i + 1], &sinfo->fun[i],
	     (sinfo->num_fun - i) * sizeof (sinfo->fun[i]));
  else if (i >= sinfo->max_fun)
    {
      bfd_size_type amt = sizeof (struct spu_elf_stack_info);
      bfd_size_type old = amt;

      old += (sinfo->max_fun - 1) * sizeof (struct function_info);
      sinfo->max_fun += 20 + (sinfo->max_fun >> 1);
      amt += (sinfo->max_fun - 1) * sizeof (struct function_info);
      sinfo = bfd_realloc (sinfo, amt);
      if (sinfo == NULL)
	return NULL;
      memset ((char *) sinfo + old, 0, amt - old);
      sec_data->stack_info = sinfo;
    }
  sinfo->fun[i].is_func = is_func;
  sinfo->fun[i].global = global;
  sinfo->fun[i].sec = sec;
  if (global)
    sinfo->fun[i].u.h = sym_h;
  else
    sinfo->fun[i].u.sym = sym_h;
  sinfo->fun[i].lo = off;
  sinfo->fun[i].hi = off + size;
  sinfo->fun[i].stack = -find_function_stack_adjust (sec, off);
  sinfo->num_fun += 1;
  return &sinfo->fun[i];
}