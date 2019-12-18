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
struct fde_entry {struct fde_entry* next; int /*<<< orphan*/ * start_address; int /*<<< orphan*/ * end_address; } ;
struct cie_entry {int dummy; } ;
struct cfi_insn_data {int dummy; } ;
typedef  int /*<<< orphan*/  segT ;

/* Variables and functions */
 int EH_FRAME_ALIGNMENT ; 
 int SEC_ALLOC ; 
 int SEC_DATA ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct fde_entry* all_fde_data ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int flag_traditional_format ; 
 int /*<<< orphan*/  output_fde (struct fde_entry*,struct cie_entry*,struct cfi_insn_data*,int) ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int) ; 
 struct cie_entry* select_cie_for_fde (struct fde_entry*,struct cfi_insn_data**) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cfi_finish (void)
{
  segT cfi_seg;
  struct fde_entry *fde;
  int save_flag_traditional_format;

  if (all_fde_data == 0)
    return;

  /* Open .eh_frame section.  */
  cfi_seg = subseg_new (".eh_frame", 0);
  bfd_set_section_flags (stdoutput, cfi_seg,
			 SEC_ALLOC | SEC_LOAD | SEC_DATA | SEC_READONLY);
  subseg_set (cfi_seg, 0);
  record_alignment (cfi_seg, EH_FRAME_ALIGNMENT);

  /* Make sure check_eh_frame doesn't do anything with our output.  */
  save_flag_traditional_format = flag_traditional_format;
  flag_traditional_format = 1;

  for (fde = all_fde_data; fde ; fde = fde->next)
    {
      struct cfi_insn_data *first;
      struct cie_entry *cie;

      if (fde->end_address == NULL)
	{
	  as_bad (_("open CFI at the end of file; missing .cfi_endproc directive"));
	  fde->end_address = fde->start_address;
	}

      cie = select_cie_for_fde (fde, &first);
      output_fde (fde, cie, first, fde->next == NULL ? EH_FRAME_ALIGNMENT : 2);
    }

  flag_traditional_format = save_flag_traditional_format;
}