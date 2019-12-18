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
struct find_targ_sec_arg {int /*<<< orphan*/ ** resultp; int /*<<< orphan*/  targ_index; } ;
struct coff_symbol {int /*<<< orphan*/  c_secnum; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_section_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct find_targ_sec_arg*) ; 
 int /*<<< orphan*/  find_targ_sec ; 
 TYPE_1__* objfile ; 

__attribute__((used)) static CORE_ADDR
cs_section_address (struct coff_symbol *cs, bfd *abfd)
{
  asection *sect = NULL;
  struct find_targ_sec_arg args;
  CORE_ADDR addr = 0;

  args.targ_index = cs->c_secnum;
  args.resultp = &sect;
  bfd_map_over_sections (abfd, find_targ_sec, &args);
  if (sect != NULL)
    addr = bfd_get_section_vma (objfile->obfd, sect);
  return addr;
}