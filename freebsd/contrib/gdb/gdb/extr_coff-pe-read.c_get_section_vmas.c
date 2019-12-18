#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct read_pe_section_data {scalar_t__ rva_start; scalar_t__ vma_offset; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int PE_SECTION_INDEX_INVALID ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int read_pe_section_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_section_vmas (bfd *abfd, asection *sectp, void *context)
{
  struct read_pe_section_data *sections = context;
  int sectix = read_pe_section_index (sectp->name);

  if (sectix != PE_SECTION_INDEX_INVALID)
    {
      /* Data within the section start at rva_start in the pe and at
         bfd_get_section_vma() within memory. Store the offset. */

      sections[sectix].vma_offset
	= bfd_get_section_vma (abfd, sectp) - sections[sectix].rva_start;
    }
}