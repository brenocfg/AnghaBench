#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct elf_segment_map {scalar_t__ p_type; int p_flags_valid; int p_paddr_valid; int p_align_valid; int includes_filehdr; int includes_phdrs; unsigned int count; struct elf_segment_map* next; int /*<<< orphan*/ * sections; scalar_t__ p_vaddr_offset; int /*<<< orphan*/  p_align; scalar_t__ p_paddr; int /*<<< orphan*/  p_flags; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_15__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_16__ {int /*<<< orphan*/  output_section; struct TYPE_16__* next; int /*<<< orphan*/  lma; } ;
typedef  TYPE_2__ asection ;
struct TYPE_20__ {int /*<<< orphan*/  this_hdr; } ;
struct TYPE_19__ {struct elf_segment_map* segment_map; TYPE_3__* phdr; } ;
struct TYPE_18__ {unsigned int e_phnum; scalar_t__ e_ehsize; int e_phentsize; scalar_t__ e_phoff; } ;
struct TYPE_17__ {scalar_t__ p_type; scalar_t__ p_offset; scalar_t__ p_filesz; scalar_t__ p_paddr; int /*<<< orphan*/  p_align; int /*<<< orphan*/  p_flags; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Shdr ;
typedef  TYPE_3__ Elf_Internal_Phdr ;
typedef  TYPE_4__ Elf_Internal_Ehdr ;

/* Variables and functions */
 scalar_t__ ELF_IS_SECTION_IN_SEGMENT_FILE (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ PT_LOAD ; 
 scalar_t__ PT_NULL ; 
 scalar_t__ TRUE ; 
 struct elf_segment_map* bfd_zalloc (TYPE_1__*,int) ; 
 TYPE_4__* elf_elfheader (TYPE_1__*) ; 
 TYPE_7__* elf_section_data (TYPE_2__*) ; 
 TYPE_5__* elf_tdata (TYPE_1__*) ; 

__attribute__((used)) static bfd_boolean
copy_elf_program_header (bfd *ibfd, bfd *obfd)
{
  Elf_Internal_Ehdr *iehdr;
  struct elf_segment_map *map;
  struct elf_segment_map *map_first;
  struct elf_segment_map **pointer_to_map;
  Elf_Internal_Phdr *segment;
  unsigned int i;
  unsigned int num_segments;
  bfd_boolean phdr_included = FALSE;

  iehdr = elf_elfheader (ibfd);

  map_first = NULL;
  pointer_to_map = &map_first;

  num_segments = elf_elfheader (ibfd)->e_phnum;
  for (i = 0, segment = elf_tdata (ibfd)->phdr;
       i < num_segments;
       i++, segment++)
    {
      asection *section;
      unsigned int section_count;
      bfd_size_type amt;
      Elf_Internal_Shdr *this_hdr;
      asection *first_section = NULL;

      /* FIXME: Do we need to copy PT_NULL segment?  */
      if (segment->p_type == PT_NULL)
	continue;

      /* Compute how many sections are in this segment.  */
      for (section = ibfd->sections, section_count = 0;
	   section != NULL;
	   section = section->next)
	{
	  this_hdr = &(elf_section_data(section)->this_hdr);
	  if (ELF_IS_SECTION_IN_SEGMENT_FILE (this_hdr, segment))
	    {
	      if (!first_section)
		first_section = section;
	      section_count++;
	    }
	}

      /* Allocate a segment map big enough to contain
	 all of the sections we have selected.  */
      amt = sizeof (struct elf_segment_map);
      if (section_count != 0)
	amt += ((bfd_size_type) section_count - 1) * sizeof (asection *);
      map = bfd_zalloc (obfd, amt);
      if (map == NULL)
	return FALSE;

      /* Initialize the fields of the output segment map with the
	 input segment.  */
      map->next = NULL;
      map->p_type = segment->p_type;
      map->p_flags = segment->p_flags;
      map->p_flags_valid = 1;
      map->p_paddr = segment->p_paddr;
      map->p_paddr_valid = 1;
      map->p_align = segment->p_align;
      map->p_align_valid = 1;
      map->p_vaddr_offset = 0;

      /* Determine if this segment contains the ELF file header
	 and if it contains the program headers themselves.  */
      map->includes_filehdr = (segment->p_offset == 0
			       && segment->p_filesz >= iehdr->e_ehsize);

      map->includes_phdrs = 0;
      if (! phdr_included || segment->p_type != PT_LOAD)
	{
	  map->includes_phdrs =
	    (segment->p_offset <= (bfd_vma) iehdr->e_phoff
	     && (segment->p_offset + segment->p_filesz
		 >= ((bfd_vma) iehdr->e_phoff
		     + iehdr->e_phnum * iehdr->e_phentsize)));

	  if (segment->p_type == PT_LOAD && map->includes_phdrs)
	    phdr_included = TRUE;
	}

      if (!map->includes_phdrs && !map->includes_filehdr)
	/* There is some other padding before the first section.  */
	map->p_vaddr_offset = ((first_section ? first_section->lma : 0)
			       - segment->p_paddr);

      if (section_count != 0)
	{
	  unsigned int isec = 0;

	  for (section = first_section;
	       section != NULL;
	       section = section->next)
	    {
	      this_hdr = &(elf_section_data(section)->this_hdr);
	      if (ELF_IS_SECTION_IN_SEGMENT_FILE (this_hdr, segment))
		{
		  map->sections[isec++] = section->output_section;
		  if (isec == section_count)
		    break;
		}
	    }
	}

      map->count = section_count;
      *pointer_to_map = map;
      pointer_to_map = &map->next;
    }

  elf_tdata (obfd)->segment_map = map_first;
  return TRUE;
}