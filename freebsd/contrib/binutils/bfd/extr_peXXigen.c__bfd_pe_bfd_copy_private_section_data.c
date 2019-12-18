#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pei_section_tdata {int dummy; } ;
struct coff_section_tdata {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int /*<<< orphan*/ * used_by_bfd; } ;
typedef  TYPE_1__ asection ;
struct TYPE_10__ {int /*<<< orphan*/ * tdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  pe_flags; int /*<<< orphan*/  virt_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_coff_flavour ; 
 void* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* coff_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* pei_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

bfd_boolean
_bfd_XX_bfd_copy_private_section_data (bfd *ibfd,
				       asection *isec,
				       bfd *obfd,
				       asection *osec)
{
  if (bfd_get_flavour (ibfd) != bfd_target_coff_flavour
      || bfd_get_flavour (obfd) != bfd_target_coff_flavour)
    return TRUE;

  if (coff_section_data (ibfd, isec) != NULL
      && pei_section_data (ibfd, isec) != NULL)
    {
      if (coff_section_data (obfd, osec) == NULL)
	{
	  bfd_size_type amt = sizeof (struct coff_section_tdata);
	  osec->used_by_bfd = bfd_zalloc (obfd, amt);
	  if (osec->used_by_bfd == NULL)
	    return FALSE;
	}

      if (pei_section_data (obfd, osec) == NULL)
	{
	  bfd_size_type amt = sizeof (struct pei_section_tdata);
	  coff_section_data (obfd, osec)->tdata = bfd_zalloc (obfd, amt);
	  if (coff_section_data (obfd, osec)->tdata == NULL)
	    return FALSE;
	}

      pei_section_data (obfd, osec)->virt_size =
	pei_section_data (ibfd, isec)->virt_size;
      pei_section_data (obfd, osec)->pe_flags =
	pei_section_data (ibfd, isec)->pe_flags;
    }

  return TRUE;
}