#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pe_tdata {int dummy; } ;
struct TYPE_10__ {int pe; } ;
struct TYPE_11__ {int force_minimum_alignment; int /*<<< orphan*/  target_subsystem; int /*<<< orphan*/  in_reloc_p; TYPE_2__ coff; } ;
typedef  TYPE_3__ pe_data_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {struct pe_tdata* pe_obj_data; } ;
struct TYPE_12__ {TYPE_1__ tdata; } ;
typedef  TYPE_4__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PEI_TARGET_SUBSYSTEM ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_zalloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  in_reloc_p ; 
 TYPE_3__* pe_data (TYPE_4__*) ; 

__attribute__((used)) static bfd_boolean
pe_mkobject (bfd * abfd)
{
  pe_data_type *pe;
  bfd_size_type amt = sizeof (pe_data_type);

  abfd->tdata.pe_obj_data = (struct pe_tdata *) bfd_zalloc (abfd, amt);

  if (abfd->tdata.pe_obj_data == 0)
    return FALSE;

  pe = pe_data (abfd);

  pe->coff.pe = 1;

  /* in_reloc_p is architecture dependent.  */
  pe->in_reloc_p = in_reloc_p;

#ifdef PEI_FORCE_MINIMUM_ALIGNMENT
  pe->force_minimum_alignment = 1;
#endif
#ifdef PEI_TARGET_SUBSYSTEM
  pe->target_subsystem = PEI_TARGET_SUBSYSTEM;
#endif

  return TRUE;
}