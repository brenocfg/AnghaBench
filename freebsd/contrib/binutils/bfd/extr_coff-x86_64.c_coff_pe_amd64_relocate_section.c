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
struct internal_syment {int dummy; } ;
struct internal_reloc {int dummy; } ;
struct bfd_link_info {scalar_t__ relocatable; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_coff_generic_relocate_section (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_reloc*,struct internal_syment*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bfd_boolean
coff_pe_amd64_relocate_section (bfd *output_bfd,
				struct bfd_link_info *info,
				bfd *input_bfd,
				asection *input_section,
				bfd_byte *contents,
				struct internal_reloc *relocs,
				struct internal_syment *syms,
				asection **sections)
{
  if (info->relocatable)
    return TRUE;

  return _bfd_coff_generic_relocate_section (output_bfd, info, input_bfd,input_section, contents,relocs, syms, sections);
}