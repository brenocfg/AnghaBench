#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ value; TYPE_7__* section; } ;
struct TYPE_18__ {TYPE_2__ def; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; int /*<<< orphan*/  def_regular; scalar_t__ def_dynamic; } ;
struct elf_backend_data {TYPE_5__* s; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_21__ {int flags; } ;
typedef  TYPE_6__ bfd ;
struct TYPE_22__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_7__ asection ;
struct TYPE_23__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_20__ {int int_rels_per_ext_rel; } ;
struct TYPE_16__ {int target_index; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Shdr ;
typedef  TYPE_8__ Elf_Internal_Rela ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  ELF32_R_INFO (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int EXEC_P ; 
 int NUM_SHDR_ENTRIES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_elf_link_output_relocs (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_8__*,struct elf_link_hash_entry**) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_6__*) ; 

bfd_boolean
elf_vxworks_emit_relocs (bfd *output_bfd,
			 asection *input_section,
			 Elf_Internal_Shdr *input_rel_hdr,
			 Elf_Internal_Rela *internal_relocs,
			 struct elf_link_hash_entry **rel_hash)
{
  const struct elf_backend_data *bed;
  Elf_Internal_Rela *irela;
  Elf_Internal_Rela *irelaend;
  int j;

  bed = get_elf_backend_data (output_bfd);

  irela = internal_relocs;
  irelaend = irela + (NUM_SHDR_ENTRIES (input_rel_hdr)
		      * bed->s->int_rels_per_ext_rel);
  while (irela < irelaend)
    {
      if ((output_bfd->flags & (DYNAMIC|EXEC_P))
	  && *rel_hash
	  && (*rel_hash)->def_dynamic
	  && !(*rel_hash)->def_regular
	  && ((*rel_hash)->root.type == bfd_link_hash_defined
	      || (*rel_hash)->root.type == bfd_link_hash_defweak)
	  && (*rel_hash)->root.u.def.section->output_section != NULL)
	{
	  /* This is a relocation from an executable or shared library
	     against a symbol in a different shared library.  We are
	     creating a definition in the output file but it does not come
	     from any of our normal (.o) files. ie. a PLT stub.
	     Normally this would be a relocation against against SHN_UNDEF
	     with the VMA of the PLT stub.  This upsets the VxWorks loader.
	     Convert it to a section-relative relocation.
	     This gets some other symbols (for instance .dynbss),
	     but is conservatively correct.  */
	  for (j = 0; j < bed->s->int_rels_per_ext_rel; j++)
	    {
	      asection *sec = (*rel_hash)->root.u.def.section;
	      int this_idx = sec->output_section->target_index;

	      irela[j].r_info = ELF32_R_INFO (this_idx,
		  ELF32_R_TYPE (irela[j].r_info));
	      irela[j].r_addend += (*rel_hash)->root.u.def.value;
	      irela[j].r_addend += sec->output_offset;
	    }
	  /* Stop the generic routine adjusting this entry.  */
	  *rel_hash = NULL;
	}
      irela += bed->s->int_rels_per_ext_rel;
      rel_hash++;
    }
  return _bfd_elf_link_output_relocs (output_bfd, input_section,
				      input_rel_hdr, internal_relocs,
				      rel_hash);
}