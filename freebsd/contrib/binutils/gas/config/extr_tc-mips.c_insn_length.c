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
struct mips_cl_insn {scalar_t__ use_extend; scalar_t__ mips16_absolute_jump_p; } ;
struct TYPE_2__ {int /*<<< orphan*/  mips16; } ;

/* Variables and functions */
 TYPE_1__ mips_opts ; 

__attribute__((used)) static inline unsigned int
insn_length (const struct mips_cl_insn *insn)
{
  if (!mips_opts.mips16)
    return 4;
  return insn->mips16_absolute_jump_p || insn->use_extend ? 4 : 2;
}