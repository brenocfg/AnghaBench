#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mips_cl_insn {int dummy; } ;
struct TYPE_3__ {int fr_literal; } ;

/* Variables and functions */
 char* frag_more (int /*<<< orphan*/ ) ; 
 TYPE_1__* frag_now ; 
 int /*<<< orphan*/  insn_length (struct mips_cl_insn*) ; 
 int /*<<< orphan*/  move_insn (struct mips_cl_insn*,TYPE_1__*,char*) ; 

__attribute__((used)) static void
add_fixed_insn (struct mips_cl_insn *insn)
{
  char *f = frag_more (insn_length (insn));
  move_insn (insn, frag_now, f - frag_now->fr_literal);
}