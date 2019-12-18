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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {scalar_t__ base_file; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_9__ {TYPE_1__* output_section; scalar_t__ output_offset; scalar_t__ vma; } ;
typedef  TYPE_3__ asection ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_11__ {scalar_t__ pe; } ;
struct TYPE_8__ {scalar_t__ ImageBase; } ;
struct TYPE_10__ {TYPE_2__ pe_opthdr; } ;
struct TYPE_7__ {scalar_t__ vma; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_5__* coff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* pe_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arm_emit_base_file_entry (struct bfd_link_info *info,
			  bfd *output_bfd,
			  asection *input_section,
			  bfd_vma reloc_offset)
{
  bfd_vma addr = reloc_offset
                - input_section->vma
                + input_section->output_offset
                  + input_section->output_section->vma;

  if (coff_data (output_bfd)->pe)
     addr -= pe_data (output_bfd)->pe_opthdr.ImageBase;
  fwrite (& addr, 1, sizeof (addr), (FILE *) info->base_file);

}