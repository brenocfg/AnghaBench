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
struct TYPE_2__ {int /*<<< orphan*/  e_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF_SCORE_FIXDEP ; 
 int /*<<< orphan*/  EF_SCORE_PIC ; 
 scalar_t__ PIC ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ ) ; 
 int fix_data_dependency ; 
 scalar_t__ score_pic ; 
 int /*<<< orphan*/  stdoutput ; 

void
score_elf_final_processing (void)
{
  if (fix_data_dependency == 1)
    {
      elf_elfheader (stdoutput)->e_flags |= EF_SCORE_FIXDEP;
    }
  if (score_pic == PIC)
    {
      elf_elfheader (stdoutput)->e_flags |= EF_SCORE_PIC;
    }
}