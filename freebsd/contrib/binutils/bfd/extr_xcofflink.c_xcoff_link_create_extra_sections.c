#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {scalar_t__ strip; TYPE_1__* hash; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {scalar_t__ xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_10__ {int alignment_power; } ;
typedef  TYPE_3__ asection ;
struct TYPE_11__ {TYPE_3__* debug_section; TYPE_3__* descriptor_section; TYPE_3__* toc_section; TYPE_3__* linkage_section; TYPE_3__* loader_section; } ;
struct TYPE_8__ {scalar_t__ creator; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* bfd_make_section_anyway_with_flags (TYPE_2__*,char*,int) ; 
 scalar_t__ strip_all ; 
 TYPE_5__* xcoff_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
xcoff_link_create_extra_sections (bfd * abfd, struct bfd_link_info *info)
{
  bfd_boolean return_value = FALSE;

  if (info->hash->creator == abfd->xvec)
    {
      /* We need to build a .loader section, so we do it here.  This
	 won't work if we're producing an XCOFF output file with no
	 XCOFF input files.  FIXME.  */

      if (xcoff_hash_table (info)->loader_section == NULL)
	{
	  asection *lsec;
	  flagword flags = SEC_HAS_CONTENTS | SEC_IN_MEMORY;

	  lsec = bfd_make_section_anyway_with_flags (abfd, ".loader", flags);
	  if (lsec == NULL)
	    goto end_return;

	  xcoff_hash_table (info)->loader_section = lsec;
	}

      /* Likewise for the linkage section.  */
      if (xcoff_hash_table (info)->linkage_section == NULL)
	{
	  asection *lsec;
	  flagword flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS
			    | SEC_IN_MEMORY);

	  lsec = bfd_make_section_anyway_with_flags (abfd, ".gl", flags);
	  if (lsec == NULL)
	    goto end_return;

	  xcoff_hash_table (info)->linkage_section = lsec;
	  lsec->alignment_power = 2;
	}

      /* Likewise for the TOC section.  */
      if (xcoff_hash_table (info)->toc_section == NULL)
	{
	  asection *tsec;
	  flagword flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS
			    | SEC_IN_MEMORY);

	  tsec = bfd_make_section_anyway_with_flags (abfd, ".tc", flags);
	  if (tsec == NULL)
	    goto end_return;

	  xcoff_hash_table (info)->toc_section = tsec;
	  tsec->alignment_power = 2;
	}

      /* Likewise for the descriptor section.  */
      if (xcoff_hash_table (info)->descriptor_section == NULL)
	{
	  asection *dsec;
	  flagword flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS
			    | SEC_IN_MEMORY);

	  dsec = bfd_make_section_anyway_with_flags (abfd, ".ds", flags);
	  if (dsec == NULL)
	    goto end_return;

	  xcoff_hash_table (info)->descriptor_section = dsec;
	  dsec->alignment_power = 2;
	}

      /* Likewise for the .debug section.  */
      if (xcoff_hash_table (info)->debug_section == NULL
	  && info->strip != strip_all)
	{
	  asection *dsec;
	  flagword flags = SEC_HAS_CONTENTS | SEC_IN_MEMORY;

	  dsec = bfd_make_section_anyway_with_flags (abfd, ".debug", flags);
	  if (dsec == NULL)
	    goto end_return;

	  xcoff_hash_table (info)->debug_section = dsec;
	}
    }

  return_value = TRUE;

 end_return:

  return return_value;
}