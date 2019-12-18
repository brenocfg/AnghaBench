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
typedef  int /*<<< orphan*/  symbolS ;
struct mips_cl_insn {int fixed_p; } ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_3__ {scalar_t__ fr_literal; } ;

/* Variables and functions */
 int /*<<< orphan*/  frag_grow (int) ; 
 scalar_t__ frag_more (int /*<<< orphan*/ ) ; 
 TYPE_1__* frag_now ; 
 int /*<<< orphan*/  frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_insn (struct mips_cl_insn*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  rs_machine_dependent ; 

__attribute__((used)) static void
add_relaxed_insn (struct mips_cl_insn *insn, int max_chars, int var,
		  relax_substateT subtype, symbolS *symbol, offsetT offset)
{
  frag_grow (max_chars);
  move_insn (insn, frag_now, frag_more (0) - frag_now->fr_literal);
  insn->fixed_p = 1;
  frag_var (rs_machine_dependent, max_chars, var,
	    subtype, symbol, offset, NULL);
}