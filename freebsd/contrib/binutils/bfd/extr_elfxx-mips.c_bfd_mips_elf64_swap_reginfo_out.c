#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  ri_gp_value; int /*<<< orphan*/ * ri_cprmask; int /*<<< orphan*/  ri_pad; int /*<<< orphan*/  ri_gprmask; } ;
struct TYPE_5__ {int /*<<< orphan*/  ri_gp_value; int /*<<< orphan*/ * ri_cprmask; int /*<<< orphan*/  ri_pad; int /*<<< orphan*/  ri_gprmask; } ;
typedef  TYPE_1__ Elf64_Internal_RegInfo ;
typedef  TYPE_2__ Elf64_External_RegInfo ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfd_mips_elf64_swap_reginfo_out (bfd *abfd, const Elf64_Internal_RegInfo *in,
				 Elf64_External_RegInfo *ex)
{
  H_PUT_32 (abfd, in->ri_gprmask, ex->ri_gprmask);
  H_PUT_32 (abfd, in->ri_pad, ex->ri_pad);
  H_PUT_32 (abfd, in->ri_cprmask[0], ex->ri_cprmask[0]);
  H_PUT_32 (abfd, in->ri_cprmask[1], ex->ri_cprmask[1]);
  H_PUT_32 (abfd, in->ri_cprmask[2], ex->ri_cprmask[2]);
  H_PUT_32 (abfd, in->ri_cprmask[3], ex->ri_cprmask[3]);
  H_PUT_64 (abfd, in->ri_gp_value, ex->ri_gp_value);
}