#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {int flags; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ asection ;
struct TYPE_11__ {int sh_entsize; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; } ;
typedef  TYPE_3__ Elf_Internal_Shdr ;

/* Variables and functions */
 int DYNAMIC ; 
 int SEC_SMALL_DATA ; 
 int /*<<< orphan*/  SHF_ALPHA_GPREL ; 
 int /*<<< orphan*/  SHT_ALPHA_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_get_section_name (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_fake_sections (bfd *abfd, Elf_Internal_Shdr *hdr, asection *sec)
{
  register const char *name;

  name = bfd_get_section_name (abfd, sec);

  if (strcmp (name, ".mdebug") == 0)
    {
      hdr->sh_type = SHT_ALPHA_DEBUG;
      /* In a shared object on Irix 5.3, the .mdebug section has an
         entsize of 0.  FIXME: Does this matter?  */
      if ((abfd->flags & DYNAMIC) != 0 )
	hdr->sh_entsize = 0;
      else
	hdr->sh_entsize = 1;
    }
  else if ((sec->flags & SEC_SMALL_DATA)
	   || strcmp (name, ".sdata") == 0
	   || strcmp (name, ".sbss") == 0
	   || strcmp (name, ".lit4") == 0
	   || strcmp (name, ".lit8") == 0)
    hdr->sh_flags |= SHF_ALPHA_GPREL;

  return TRUE;
}