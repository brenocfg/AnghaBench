#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct elf_final_link_info {TYPE_2__* info; TYPE_9__** sections; TYPE_10__* internal_syms; } ;
struct TYPE_25__ {char* string; } ;
struct TYPE_22__ {scalar_t__ value; TYPE_4__* section; } ;
struct TYPE_23__ {TYPE_5__ def; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_8__ root; TYPE_6__ u; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_26__ {TYPE_1__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_9__ asection ;
struct TYPE_24__ {scalar_t__ vma; } ;
struct TYPE_21__ {scalar_t__ output_offset; TYPE_3__* output_section; } ;
struct TYPE_20__ {scalar_t__ vma; } ;
struct TYPE_19__ {int /*<<< orphan*/  hash; } ;
struct TYPE_18__ {char* name; scalar_t__ vma; } ;
struct TYPE_17__ {scalar_t__ output_offset; TYPE_7__* output_section; } ;
struct TYPE_15__ {int /*<<< orphan*/  sh_link; } ;
struct TYPE_16__ {TYPE_11__ symtab_hdr; } ;
struct TYPE_14__ {scalar_t__ st_shndx; scalar_t__ st_value; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_10__ Elf_Internal_Sym ;
typedef  TYPE_11__ Elf_Internal_Shdr ;

/* Variables and functions */
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STB_LOCAL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_13__* bfd_com_section_ptr ; 
 char* bfd_elf_string_from_elf_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bfd_boolean 
resolve_symbol (const char *                  name,
		bfd *                         input_bfd,
		struct elf_final_link_info *  finfo,
		bfd_vma *                     result,
		size_t                        locsymcount)
{
  Elf_Internal_Sym *            sym;
  struct bfd_link_hash_entry *  global_entry;
  const char *                  candidate = NULL;
  Elf_Internal_Shdr *           symtab_hdr;
  asection *                    sec = NULL;
  size_t                        i;
  
  symtab_hdr = & elf_tdata (input_bfd)->symtab_hdr;

  for (i = 0; i < locsymcount; ++ i)
    {
      sym = finfo->internal_syms + i;
      sec = finfo->sections [i];

      if (ELF_ST_BIND (sym->st_info) != STB_LOCAL)
	continue;

      candidate = bfd_elf_string_from_elf_section (input_bfd,
						   symtab_hdr->sh_link,
						   sym->st_name);
#ifdef DEBUG
      printf ("Comparing string: '%s' vs. '%s' = 0x%x\n", 
	      name, candidate, (unsigned int)sym->st_value);
#endif
      if (candidate && strcmp (candidate, name) == 0)
	{
	  * result = sym->st_value;

	  if (sym->st_shndx > SHN_UNDEF && 
	      sym->st_shndx < SHN_LORESERVE)
	    {
#ifdef DEBUG
	      printf ("adjusting for sec '%s' @ 0x%x + 0x%x\n",
		      sec->output_section->name, 
		      (unsigned int)sec->output_section->vma, 
		      (unsigned int)sec->output_offset);
#endif
	      * result += sec->output_offset + sec->output_section->vma;
	    }
#ifdef DEBUG
	  printf ("Found symbol with effective value %8.8x\n", (unsigned int)* result);
#endif
	  return TRUE;
	}
    }

  /* Hmm, haven't found it yet. perhaps it is a global.  */
  global_entry = bfd_link_hash_lookup (finfo->info->hash, name, FALSE, FALSE, TRUE);
  if (!global_entry)
    return FALSE;
  
  if (global_entry->type == bfd_link_hash_defined
      || global_entry->type == bfd_link_hash_defweak)
    {
      * result = global_entry->u.def.value 
	+ global_entry->u.def.section->output_section->vma 
	+ global_entry->u.def.section->output_offset;
#ifdef DEBUG
      printf ("Found GLOBAL symbol '%s' with value %8.8x\n",
	      global_entry->root.string, (unsigned int)*result);
#endif
      return TRUE;
    } 

  if (global_entry->type == bfd_link_hash_common)
    {
      *result = global_entry->u.def.value +
	bfd_com_section_ptr->output_section->vma +
	bfd_com_section_ptr->output_offset;
#ifdef DEBUG
      printf ("Found COMMON symbol '%s' with value %8.8x\n",
	      global_entry->root.string, (unsigned int)*result);
#endif
      return TRUE;
    }
  
  return FALSE;
}