#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {scalar_t__ num_exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_filler_bfd (int) ; 
 int /*<<< orphan*/  generate_edata (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 TYPE_1__* pe_def_file ; 
 int /*<<< orphan*/  pe_dll_id_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_def_file (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

void
pe_dll_build_sections (bfd *abfd, struct bfd_link_info *info)
{
  pe_dll_id_target (bfd_get_target (abfd));
  process_def_file (abfd, info);

  if (pe_def_file->num_exports == 0 && !info->shared)
    return;

  generate_edata (abfd, info);
  build_filler_bfd (1);
}