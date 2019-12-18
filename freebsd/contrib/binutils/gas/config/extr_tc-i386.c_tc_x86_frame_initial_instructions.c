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

/* Variables and functions */
 scalar_t__ CODE_64BIT ; 
 int /*<<< orphan*/  cfi_add_CFA_def_cfa (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_add_CFA_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_code ; 
 unsigned int tc_x86_regname_to_dw2regnum (char*) ; 
 int /*<<< orphan*/  x86_cie_data_alignment ; 
 int /*<<< orphan*/  x86_dwarf2_return_column ; 

void
tc_x86_frame_initial_instructions (void)
{
  static unsigned int sp_regno;

  if (!sp_regno)
    sp_regno = tc_x86_regname_to_dw2regnum (flag_code == CODE_64BIT
					    ? "rsp" : "esp");

  cfi_add_CFA_def_cfa (sp_regno, -x86_cie_data_alignment);
  cfi_add_CFA_offset (x86_dwarf2_return_column, x86_cie_data_alignment);
}