#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  X_add_symbol; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_6__ exp; int /*<<< orphan*/  pc_rel; } ;
struct score_it {int instruction; int relax_inst; scalar_t__ size; int relax_size; TYPE_2__ reloc; int /*<<< orphan*/  type; } ;
typedef  enum insn_class { ____Placeholder_insn_class } insn_class ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_7__ {int /*<<< orphan*/  is_insn; } ;
struct TYPE_9__ {char* fr_literal; TYPE_1__ tc_frag_data; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_NONE ; 
 scalar_t__ FALSE ; 
 int GET_INSN_CLASS (int /*<<< orphan*/ ) ; 
 int INSN_CLASS_16 ; 
 int INSN_CLASS_32 ; 
 int INSN_CLASS_PCE ; 
 scalar_t__ INSN_SIZE ; 
 int /*<<< orphan*/  Insn_Type_PCE ; 
 int /*<<< orphan*/  RELAX_ENCODE (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RELAX_PAD_BYTE ; 
 scalar_t__ TRUE ; 
 void* adjust_paritybit (int,int) ; 
 int /*<<< orphan*/  dwarf2_emit_insn (int) ; 
 int /*<<< orphan*/  fix_new_score (TYPE_3__*,int,int,TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  frag_grow (int) ; 
 char* frag_more (scalar_t__) ; 
 int /*<<< orphan*/  frag_new (int /*<<< orphan*/ ) ; 
 TYPE_3__* frag_now ; 
 scalar_t__ frag_now_fix () ; 
 char* frag_var (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_wane (TYPE_3__*) ; 
 int g_opt ; 
 int /*<<< orphan*/  handle_dependency (struct score_it*) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct score_it*,struct score_it*,int) ; 
 int /*<<< orphan*/  rs_machine_dependent ; 

__attribute__((used)) static void
gen_insn_frag (struct score_it *part_1, struct score_it *part_2)
{
  char *p;
  bfd_boolean pce_p = FALSE;
  int relaxable_p = g_opt;
  int relax_size = 0;
  struct score_it *inst1 = part_1;
  struct score_it *inst2 = part_2;
  struct score_it backup_inst1;

  pce_p = (inst2) ? TRUE : FALSE;
  memcpy (&backup_inst1, inst1, sizeof (struct score_it));

  /* Adjust instruction opcode and to be relaxed instruction opcode.  */
  if (pce_p)
    {
      backup_inst1.instruction = ((backup_inst1.instruction & 0x7FFF) << 15)
                                  | (inst2->instruction & 0x7FFF);
      backup_inst1.instruction = adjust_paritybit (backup_inst1.instruction, INSN_CLASS_PCE);
      backup_inst1.relax_inst = 0x8000;
      backup_inst1.size = INSN_SIZE;
      backup_inst1.relax_size = 0;
      backup_inst1.type = Insn_Type_PCE;
    }
  else
    {
      backup_inst1.instruction = adjust_paritybit (backup_inst1.instruction,
						   GET_INSN_CLASS (backup_inst1.type));
    }

  if (backup_inst1.relax_size != 0)
    {
      enum insn_class tmp;

      tmp = (backup_inst1.size == INSN_SIZE) ? INSN_CLASS_16 : INSN_CLASS_32;
      backup_inst1.relax_inst = adjust_paritybit (backup_inst1.relax_inst, tmp);
    }

  /* Check data dependency.  */
  handle_dependency (&backup_inst1);

  /* Start a new frag if frag_now is not empty and is not instruction frag, maybe it contains
     data produced by .ascii etc.  Doing this is to make one instruction per frag.  */
  if (frag_now_fix () != 0)
    {
      if (!frag_now->tc_frag_data.is_insn)
	frag_wane (frag_now);

      frag_new (0);
    }

  /* Here, we must call frag_grow in order to keep the instruction frag type is
     rs_machine_dependent.
     For, frag_var may change frag_now->fr_type to rs_fill by calling frag_grow which
     acturally will call frag_wane.
     Calling frag_grow first will create a new frag_now which free size is 20 that is enough
     for frag_var.  */
  frag_grow (20);

  p = frag_more (backup_inst1.size);
  md_number_to_chars (p, backup_inst1.instruction, backup_inst1.size);

#ifdef OBJ_ELF
  dwarf2_emit_insn (backup_inst1.size);
#endif

  /* Generate fixup structure.  */
  if (pce_p)
    {
      if (inst1->reloc.type != BFD_RELOC_NONE)
	fix_new_score (frag_now, p - frag_now->fr_literal,
		       inst1->size, &inst1->reloc.exp,
		       inst1->reloc.pc_rel, inst1->reloc.type);

      if (inst2->reloc.type != BFD_RELOC_NONE)
	fix_new_score (frag_now, p - frag_now->fr_literal + 2,
		       inst2->size, &inst2->reloc.exp, inst2->reloc.pc_rel, inst2->reloc.type);
    }
  else
    {
      if (backup_inst1.reloc.type != BFD_RELOC_NONE)
	fix_new_score (frag_now, p - frag_now->fr_literal,
		       backup_inst1.size, &backup_inst1.reloc.exp,
		       backup_inst1.reloc.pc_rel, backup_inst1.reloc.type);
    }

  /* relax_size may be 2, 4, 12 or 0, 0 indicates no relaxation.  */
  relaxable_p &= (backup_inst1.relax_size != 0);
  relax_size = relaxable_p ? backup_inst1.relax_size : 0;

  p = frag_var (rs_machine_dependent, relax_size + RELAX_PAD_BYTE, 0,
                RELAX_ENCODE (backup_inst1.size, backup_inst1.relax_size,
                              backup_inst1.type, 0, 0, relaxable_p),
                backup_inst1.reloc.exp.X_add_symbol, 0, NULL);

  if (relaxable_p)
    md_number_to_chars (p, backup_inst1.relax_inst, relax_size);

  memcpy (inst1, &backup_inst1, sizeof (struct score_it));
}