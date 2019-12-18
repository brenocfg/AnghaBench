#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_fake_sections ) (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ;TYPE_2__* s; int /*<<< orphan*/  may_use_rel_p; int /*<<< orphan*/  may_use_rela_p; } ;
struct bfd_link_order {scalar_t__ offset; scalar_t__ size; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {struct bfd_link_order* link_order; } ;
struct TYPE_15__ {int flags; scalar_t__ size; int alignment_power; int entsize; int /*<<< orphan*/  use_rela_p; TYPE_1__ map_tail; scalar_t__ vma; scalar_t__ user_set_vma; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ asection ;
struct TYPE_16__ {unsigned int sh_name; scalar_t__ sh_size; int sh_addralign; int sh_type; int sh_entsize; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_info; int /*<<< orphan*/ * contents; TYPE_3__* bfd_section; scalar_t__ sh_link; scalar_t__ sh_offset; scalar_t__ sh_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  rel_hdr; TYPE_4__ this_hdr; } ;
struct TYPE_17__ {int /*<<< orphan*/  cverrefs; int /*<<< orphan*/  cverdefs; } ;
struct TYPE_14__ {int sizeof_hash_entry; int sizeof_sym; int sizeof_dyn; int sizeof_rela; int sizeof_rel; int arch_size; } ;
typedef  TYPE_4__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf_External_Versym ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GRP_ENTRY_SIZE ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_GROUP ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int SEC_MERGE ; 
 int SEC_NEVER_LOAD ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int SEC_STRINGS ; 
 int SEC_THREAD_LOCAL ; 
 int /*<<< orphan*/  SHF_ALLOC ; 
 int /*<<< orphan*/  SHF_EXECINSTR ; 
 int /*<<< orphan*/  SHF_GROUP ; 
 int /*<<< orphan*/  SHF_MERGE ; 
 int /*<<< orphan*/  SHF_STRINGS ; 
 int /*<<< orphan*/  SHF_TLS ; 
 int /*<<< orphan*/  SHF_WRITE ; 
#define  SHT_DYNAMIC 144 
#define  SHT_DYNSYM 143 
#define  SHT_FINI_ARRAY 142 
#define  SHT_GNU_HASH 141 
#define  SHT_GNU_verdef 140 
#define  SHT_GNU_verneed 139 
#define  SHT_GNU_versym 138 
#define  SHT_GROUP 137 
#define  SHT_HASH 136 
#define  SHT_INIT_ARRAY 135 
#define  SHT_NOBITS 134 
#define  SHT_NOTE 133 
 int SHT_NULL ; 
#define  SHT_PREINIT_ARRAY 132 
#define  SHT_PROGBITS 131 
#define  SHT_REL 130 
#define  SHT_RELA 129 
#define  SHT_STRTAB 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _bfd_elf_init_reloc_shdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _bfd_elf_strtab_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_group_name (TYPE_3__*) ; 
 TYPE_8__* elf_section_data (TYPE_3__*) ; 
 int /*<<< orphan*/  elf_shstrtab (int /*<<< orphan*/ *) ; 
 TYPE_7__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void
elf_fake_sections (bfd *abfd, asection *asect, void *failedptrarg)
{
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  bfd_boolean *failedptr = failedptrarg;
  Elf_Internal_Shdr *this_hdr;
  unsigned int sh_type;

  if (*failedptr)
    {
      /* We already failed; just get out of the bfd_map_over_sections
	 loop.  */
      return;
    }

  this_hdr = &elf_section_data (asect)->this_hdr;

  this_hdr->sh_name = (unsigned int) _bfd_elf_strtab_add (elf_shstrtab (abfd),
							  asect->name, FALSE);
  if (this_hdr->sh_name == (unsigned int) -1)
    {
      *failedptr = TRUE;
      return;
    }

  /* Don't clear sh_flags. Assembler may set additional bits.  */

  if ((asect->flags & SEC_ALLOC) != 0
      || asect->user_set_vma)
    this_hdr->sh_addr = asect->vma;
  else
    this_hdr->sh_addr = 0;

  this_hdr->sh_offset = 0;
  this_hdr->sh_size = asect->size;
  this_hdr->sh_link = 0;
  this_hdr->sh_addralign = 1 << asect->alignment_power;
  /* The sh_entsize and sh_info fields may have been set already by
     copy_private_section_data.  */

  this_hdr->bfd_section = asect;
  this_hdr->contents = NULL;

  /* If the section type is unspecified, we set it based on
     asect->flags.  */
  if (this_hdr->sh_type == SHT_NULL)
    {
      if ((asect->flags & SEC_GROUP) != 0)
	this_hdr->sh_type = SHT_GROUP;
      else if ((asect->flags & SEC_ALLOC) != 0
	       && (((asect->flags & (SEC_LOAD | SEC_HAS_CONTENTS)) == 0)
		   || (asect->flags & SEC_NEVER_LOAD) != 0))
	this_hdr->sh_type = SHT_NOBITS;
      else
	this_hdr->sh_type = SHT_PROGBITS;
    }

  switch (this_hdr->sh_type)
    {
    default:
      break;

    case SHT_STRTAB:
    case SHT_INIT_ARRAY:
    case SHT_FINI_ARRAY:
    case SHT_PREINIT_ARRAY:
    case SHT_NOTE:
    case SHT_NOBITS:
    case SHT_PROGBITS:
      break;

    case SHT_HASH:
      this_hdr->sh_entsize = bed->s->sizeof_hash_entry;
      break;

    case SHT_DYNSYM:
      this_hdr->sh_entsize = bed->s->sizeof_sym;
      break;

    case SHT_DYNAMIC:
      this_hdr->sh_entsize = bed->s->sizeof_dyn;
      break;

    case SHT_RELA:
      if (get_elf_backend_data (abfd)->may_use_rela_p)
	this_hdr->sh_entsize = bed->s->sizeof_rela;
      break;

     case SHT_REL:
      if (get_elf_backend_data (abfd)->may_use_rel_p)
	this_hdr->sh_entsize = bed->s->sizeof_rel;
      break;

     case SHT_GNU_versym:
      this_hdr->sh_entsize = sizeof (Elf_External_Versym);
      break;

     case SHT_GNU_verdef:
      this_hdr->sh_entsize = 0;
      /* objcopy or strip will copy over sh_info, but may not set
	 cverdefs.  The linker will set cverdefs, but sh_info will be
	 zero.  */
      if (this_hdr->sh_info == 0)
	this_hdr->sh_info = elf_tdata (abfd)->cverdefs;
      else
	BFD_ASSERT (elf_tdata (abfd)->cverdefs == 0
		    || this_hdr->sh_info == elf_tdata (abfd)->cverdefs);
      break;

    case SHT_GNU_verneed:
      this_hdr->sh_entsize = 0;
      /* objcopy or strip will copy over sh_info, but may not set
	 cverrefs.  The linker will set cverrefs, but sh_info will be
	 zero.  */
      if (this_hdr->sh_info == 0)
	this_hdr->sh_info = elf_tdata (abfd)->cverrefs;
      else
	BFD_ASSERT (elf_tdata (abfd)->cverrefs == 0
		    || this_hdr->sh_info == elf_tdata (abfd)->cverrefs);
      break;

    case SHT_GROUP:
      this_hdr->sh_entsize = GRP_ENTRY_SIZE;
      break;

    case SHT_GNU_HASH:
      this_hdr->sh_entsize = bed->s->arch_size == 64 ? 0 : 4;
      break;
    }

  if ((asect->flags & SEC_ALLOC) != 0)
    this_hdr->sh_flags |= SHF_ALLOC;
  if ((asect->flags & SEC_READONLY) == 0)
    this_hdr->sh_flags |= SHF_WRITE;
  if ((asect->flags & SEC_CODE) != 0)
    this_hdr->sh_flags |= SHF_EXECINSTR;
  if ((asect->flags & SEC_MERGE) != 0)
    {
      this_hdr->sh_flags |= SHF_MERGE;
      this_hdr->sh_entsize = asect->entsize;
      if ((asect->flags & SEC_STRINGS) != 0)
	this_hdr->sh_flags |= SHF_STRINGS;
    }
  if ((asect->flags & SEC_GROUP) == 0 && elf_group_name (asect) != NULL)
    this_hdr->sh_flags |= SHF_GROUP;
  if ((asect->flags & SEC_THREAD_LOCAL) != 0)
    {
      this_hdr->sh_flags |= SHF_TLS;
      if (asect->size == 0
	  && (asect->flags & SEC_HAS_CONTENTS) == 0)
	{
	  struct bfd_link_order *o = asect->map_tail.link_order;

	  this_hdr->sh_size = 0;
	  if (o != NULL)
	    {
	      this_hdr->sh_size = o->offset + o->size;
	      if (this_hdr->sh_size != 0)
		this_hdr->sh_type = SHT_NOBITS;
	    }
	}
    }

  /* Check for processor-specific section types.  */
  sh_type = this_hdr->sh_type;
  if (bed->elf_backend_fake_sections
      && !(*bed->elf_backend_fake_sections) (abfd, this_hdr, asect))
    *failedptr = TRUE;

  if (sh_type == SHT_NOBITS && asect->size != 0)
    {
      /* Don't change the header type from NOBITS if we are being
	 called for objcopy --only-keep-debug.  */
      this_hdr->sh_type = sh_type;
    }

  /* If the section has relocs, set up a section header for the
     SHT_REL[A] section.  If two relocation sections are required for
     this section, it is up to the processor-specific back-end to
     create the other.  */
  if ((asect->flags & SEC_RELOC) != 0
      && !_bfd_elf_init_reloc_shdr (abfd,
				    &elf_section_data (asect)->rel_hdr,
				    asect,
				    asect->use_rela_p))
    *failedptr = TRUE;
}