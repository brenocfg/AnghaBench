#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int /*<<< orphan*/  gt_bytes; int /*<<< orphan*/  gt_g_value; } ;
struct TYPE_10__ {TYPE_2__ gt_entry; } ;
struct TYPE_7__ {int /*<<< orphan*/  gt_bytes; int /*<<< orphan*/  gt_g_value; } ;
struct TYPE_9__ {TYPE_1__ gt_entry; } ;
typedef  TYPE_3__ Elf32_gptab ;
typedef  TYPE_4__ Elf32_External_gptab ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfd_mips_elf32_swap_gptab_out (bfd *abfd, const Elf32_gptab *in,
			       Elf32_External_gptab *ex)
{
  H_PUT_32 (abfd, in->gt_entry.gt_g_value, ex->gt_entry.gt_g_value);
  H_PUT_32 (abfd, in->gt_entry.gt_bytes, ex->gt_entry.gt_bytes);
}