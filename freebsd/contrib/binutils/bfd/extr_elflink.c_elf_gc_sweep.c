#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct elf_gc_sweep_symbol_info {int /*<<< orphan*/  hide_symbol; struct bfd_link_info* info; } ;
struct elf_backend_data {int /*<<< orphan*/  elf_backend_hide_symbol; int /*<<< orphan*/  (* gc_sweep_hook ) (int /*<<< orphan*/ ,struct bfd_link_info*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct bfd_link_info {int /*<<< orphan*/  keep_memory; scalar_t__ print_gc_sections; TYPE_3__* input_bfds; } ;
typedef  int /*<<< orphan*/  (* gc_sweep_hook_fn ) (int /*<<< orphan*/ ,struct bfd_link_info*,TYPE_2__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_16__ {TYPE_2__* sections; struct TYPE_16__* link_next; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_15__ {int flags; int gc_mark; scalar_t__ size; scalar_t__ reloc_count; int /*<<< orphan*/  owner; int /*<<< orphan*/  output_section; int /*<<< orphan*/  name; struct TYPE_15__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_14__ {scalar_t__ sh_type; } ;
struct TYPE_17__ {int /*<<< orphan*/ * relocs; TYPE_1__ this_hdr; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_DEBUGGING ; 
 int SEC_EXCLUDE ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_RELOC ; 
 scalar_t__ SHT_NOTE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * _bfd_elf_link_read_relocs (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_elf_link_renumber_dynsyms (TYPE_3__*,struct bfd_link_info*,unsigned long*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_flavour (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  elf_gc_sweep_symbol ; 
 int /*<<< orphan*/  elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf_link_hash_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct elf_gc_sweep_symbol_info*) ; 
 TYPE_7__* elf_section_data (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bfd_link_info*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf_gc_sweep (bfd *abfd, struct bfd_link_info *info)
{
  bfd *sub;
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  gc_sweep_hook_fn gc_sweep_hook = bed->gc_sweep_hook;
  unsigned long section_sym_count;
  struct elf_gc_sweep_symbol_info sweep_info;

  for (sub = info->input_bfds; sub != NULL; sub = sub->link_next)
    {
      asection *o;

      if (bfd_get_flavour (sub) != bfd_target_elf_flavour)
	continue;

      for (o = sub->sections; o != NULL; o = o->next)
	{
	  /* Keep debug and special sections.  */
	  if ((o->flags & (SEC_DEBUGGING | SEC_LINKER_CREATED)) != 0
	      || elf_section_data (o)->this_hdr.sh_type == SHT_NOTE
	      || (o->flags & (SEC_ALLOC | SEC_LOAD | SEC_RELOC)) == 0)
	    o->gc_mark = 1;

	  if (o->gc_mark)
	    continue;

	  /* Skip sweeping sections already excluded.  */
	  if (o->flags & SEC_EXCLUDE)
	    continue;

	  /* Since this is early in the link process, it is simple
	     to remove a section from the output.  */
	  o->flags |= SEC_EXCLUDE;

	  if (info->print_gc_sections && o->size != 0)
	    _bfd_error_handler (_("Removing unused section '%s' in file '%B'"), sub, o->name);

	  /* But we also have to update some of the relocation
	     info we collected before.  */
	  if (gc_sweep_hook
	      && (o->flags & SEC_RELOC) != 0
	      && o->reloc_count > 0
	      && !bfd_is_abs_section (o->output_section))
	    {
	      Elf_Internal_Rela *internal_relocs;
	      bfd_boolean r;

	      internal_relocs
		= _bfd_elf_link_read_relocs (o->owner, o, NULL, NULL,
					     info->keep_memory);
	      if (internal_relocs == NULL)
		return FALSE;

	      r = (*gc_sweep_hook) (o->owner, info, o, internal_relocs);

	      if (elf_section_data (o)->relocs != internal_relocs)
		free (internal_relocs);

	      if (!r)
		return FALSE;
	    }
	}
    }

  /* Remove the symbols that were in the swept sections from the dynamic
     symbol table.  GCFIXME: Anyone know how to get them out of the
     static symbol table as well?  */
  sweep_info.info = info;
  sweep_info.hide_symbol = bed->elf_backend_hide_symbol;
  elf_link_hash_traverse (elf_hash_table (info), elf_gc_sweep_symbol,
			  &sweep_info);

  _bfd_elf_link_renumber_dynsyms (abfd, info, &section_sym_count);
  return TRUE;
}