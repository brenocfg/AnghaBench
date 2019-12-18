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
struct TYPE_6__ {int /*<<< orphan*/  info; int /*<<< orphan*/  section; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; } ;
struct TYPE_5__ {int /*<<< orphan*/  info; int /*<<< orphan*/  section; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Elf_Internal_Options ;
typedef  TYPE_2__ Elf_External_Options ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfd_mips_elf_swap_options_out (bfd *abfd, const Elf_Internal_Options *in,
			       Elf_External_Options *ex)
{
  H_PUT_8 (abfd, in->kind, ex->kind);
  H_PUT_8 (abfd, in->size, ex->size);
  H_PUT_16 (abfd, in->section, ex->section);
  H_PUT_32 (abfd, in->info, ex->info);
}