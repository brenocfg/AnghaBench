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
struct mips16_constant {struct mips16_constant* next; int /*<<< orphan*/  value; int /*<<< orphan*/  mode; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_constants_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_barrier_after (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int floor_log2 (int) ; 
 int /*<<< orphan*/  free (struct mips16_constant*) ; 
 int /*<<< orphan*/  gen_align (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_constants (struct mips16_constant *constants, rtx insn)
{
  struct mips16_constant *c, *next;
  int align;

  align = 0;
  for (c = constants; c != NULL; c = next)
    {
      /* If necessary, increase the alignment of PC.  */
      if (align < GET_MODE_SIZE (c->mode))
	{
	  int align_log = floor_log2 (GET_MODE_SIZE (c->mode));
	  insn = emit_insn_after (gen_align (GEN_INT (align_log)), insn);
	}
      align = GET_MODE_SIZE (c->mode);

      insn = emit_label_after (c->label, insn);
      insn = dump_constants_1 (c->mode, c->value, insn);

      next = c->next;
      free (c);
    }

  emit_barrier_after (insn);
}