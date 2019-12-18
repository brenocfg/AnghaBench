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
struct coff_arm_link_hash_table {int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {scalar_t__ relocatable; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  ARM2THUMB_GLUE_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  THUMB2ARM_GLUE_SECTION_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct coff_arm_link_hash_table* coff_arm_hash_table (struct bfd_link_info*) ; 

bfd_boolean
bfd_arm_get_bfd_for_interworking (bfd * 		 abfd,
				  struct bfd_link_info * info)
{
  struct coff_arm_link_hash_table * globals;
  flagword   			    flags;
  asection * 			    sec;

  /* If we are only performing a partial link do not bother
     getting a bfd to hold the glue.  */
  if (info->relocatable)
    return TRUE;

  globals = coff_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);

  if (globals->bfd_of_glue_owner != NULL)
    return TRUE;

  sec = bfd_get_section_by_name (abfd, ARM2THUMB_GLUE_SECTION_NAME);

  if (sec == NULL)
    {
      flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
	       | SEC_CODE | SEC_READONLY);
      sec = bfd_make_section_with_flags (abfd, ARM2THUMB_GLUE_SECTION_NAME,
					 flags);
      if (sec == NULL
	  || ! bfd_set_section_alignment (abfd, sec, 2))
	return FALSE;
    }

  sec = bfd_get_section_by_name (abfd, THUMB2ARM_GLUE_SECTION_NAME);

  if (sec == NULL)
    {
      flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
	       | SEC_CODE | SEC_READONLY);
      sec = bfd_make_section_with_flags (abfd, THUMB2ARM_GLUE_SECTION_NAME,
					 flags);

      if (sec == NULL
	  || ! bfd_set_section_alignment (abfd, sec, 2))
	return FALSE;
    }

  /* Save the bfd for later use.  */
  globals->bfd_of_glue_owner = abfd;

  return TRUE;
}