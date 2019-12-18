#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int /*<<< orphan*/  ImageBase; } ;
struct TYPE_7__ {TYPE_1__ pe_opthdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  filler_bfd ; 
 int /*<<< orphan*/  generate_reloc (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  image_base ; 
 int /*<<< orphan*/  lang_do_assignments () ; 
 int /*<<< orphan*/  lang_reset_memory_regions () ; 
 int /*<<< orphan*/  lang_size_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldemul_after_allocation () ; 
 TYPE_3__* pe_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pe_dll_id_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reloc_d ; 
 TYPE_2__* reloc_s ; 
 scalar_t__ reloc_sz ; 

void
pe_exe_fill_sections (bfd *abfd, struct bfd_link_info *info)
{
  pe_dll_id_target (bfd_get_target (abfd));
  image_base = pe_data (abfd)->pe_opthdr.ImageBase;

  generate_reloc (abfd, info);
  if (reloc_sz > 0)
    {
      bfd_set_section_size (filler_bfd, reloc_s, reloc_sz);

      /* Resize the sections.  */
      lang_reset_memory_regions ();
      lang_size_sections (NULL, TRUE);

      /* Redo special stuff.  */
      ldemul_after_allocation ();

      /* Do the assignments again.  */
      lang_do_assignments ();
    }
  reloc_s->contents = reloc_d;
}