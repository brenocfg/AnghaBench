#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int sh_type; int /*<<< orphan*/ * bfd_section; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_DEBUGGING ; 
#define  SHT_ALPHA_DEBUG 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_make_section_from_shdr (int /*<<< orphan*/ *,TYPE_1__*,char const*,int) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_section_from_shdr (bfd *abfd,
			       Elf_Internal_Shdr *hdr,
			       const char *name,
			       int shindex)
{
  asection *newsect;

  /* There ought to be a place to keep ELF backend specific flags, but
     at the moment there isn't one.  We just keep track of the
     sections by their name, instead.  Fortunately, the ABI gives
     suggested names for all the MIPS specific sections, so we will
     probably get away with this.  */
  switch (hdr->sh_type)
    {
    case SHT_ALPHA_DEBUG:
      if (strcmp (name, ".mdebug") != 0)
	return FALSE;
      break;
    default:
      return FALSE;
    }

  if (! _bfd_elf_make_section_from_shdr (abfd, hdr, name, shindex))
    return FALSE;
  newsect = hdr->bfd_section;

  if (hdr->sh_type == SHT_ALPHA_DEBUG)
    {
      if (! bfd_set_section_flags (abfd, newsect,
				   (bfd_get_section_flags (abfd, newsect)
				    | SEC_DEBUGGING)))
	return FALSE;
    }

  return TRUE;
}