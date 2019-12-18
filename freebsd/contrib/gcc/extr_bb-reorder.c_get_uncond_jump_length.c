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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  delete_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int get_attr_min_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 

__attribute__((used)) static int
get_uncond_jump_length (void)
{
  rtx label, jump;
  int length;

  label = emit_label_before (gen_label_rtx (), get_insns ());
  jump = emit_jump_insn (gen_jump (label));

  length = get_attr_min_length (jump);

  delete_insn (jump);
  delete_insn (label);
  return length;
}