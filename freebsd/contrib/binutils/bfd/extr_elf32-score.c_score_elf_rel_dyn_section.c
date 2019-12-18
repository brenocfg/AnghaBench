#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  SCORE_ELF_LOG_FILE_ALIGN (int /*<<< orphan*/ *) ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static asection *
score_elf_rel_dyn_section (bfd *dynobj, bfd_boolean create_p)
{
  static const char dname[] = ".rel.dyn";
  asection *sreloc;

  sreloc = bfd_get_section_by_name (dynobj, dname);
  if (sreloc == NULL && create_p)
    {
      sreloc = bfd_make_section_with_flags (dynobj, dname,
                                            (SEC_ALLOC
                                             | SEC_LOAD
                                             | SEC_HAS_CONTENTS
                                             | SEC_IN_MEMORY
                                             | SEC_LINKER_CREATED
                                             | SEC_READONLY));
      if (sreloc == NULL
	  || ! bfd_set_section_alignment (dynobj, sreloc,
					  SCORE_ELF_LOG_FILE_ALIGN (dynobj)))
	return NULL;
    }
  return sreloc; 
}