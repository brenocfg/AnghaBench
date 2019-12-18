#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int X_add_number; scalar_t__ X_add_symbol; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_4__ exp; int /*<<< orphan*/  pc_rel; } ;
struct score_it {int instruction; int relax_inst; char* name; int bwarn; scalar_t__ size; TYPE_2__ reloc; void* type; scalar_t__ relax_size; scalar_t__ error; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_insn; } ;
struct TYPE_14__ {int fr_literal; TYPE_1__ tc_frag_data; } ;
struct TYPE_12__ {int value; int /*<<< orphan*/  template; } ;

/* Variables and functions */
 scalar_t__ BAD_ARGS ; 
 scalar_t__ BFD_RELOC_NONE ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GET_INSN_CLASS (void*) ; 
 int GP ; 
 void* Insn_GP ; 
 int MAX_LITERAL_POOL_SIZE ; 
 int OPC_PSEUDOLDST_MASK ; 
 scalar_t__ PIC ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  RELAX_ENCODE (scalar_t__,scalar_t__,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ RELAX_PAD_BYTE ; 
 void* Rd_rvalueRs_SI15 ; 
 void* Rd_rvalueRs_preSI12 ; 
 int /*<<< orphan*/  _GP_IMM15 ; 
 int /*<<< orphan*/  _VALUE ; 
 void* adjust_paritybit (int,int /*<<< orphan*/ ) ; 
 int append_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_lwst_pic (int,TYPE_4__,int /*<<< orphan*/ ) ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_ldst_insn (char*) ; 
 int /*<<< orphan*/  dwarf2_emit_insn (scalar_t__) ; 
 int end_of_line (char*) ; 
 int /*<<< orphan*/  exp_macro_ldst_abs (char*) ; 
 int /*<<< orphan*/  fix_new_score (TYPE_5__*,char*,scalar_t__,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  frag_grow (int) ; 
 char* frag_more (scalar_t__) ; 
 int /*<<< orphan*/  frag_new (int /*<<< orphan*/ ) ; 
 TYPE_5__* frag_now ; 
 scalar_t__ frag_now_fix () ; 
 char* frag_var (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_wane (TYPE_5__*) ; 
 int /*<<< orphan*/  gen_insn_frag (struct score_it*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_dependency (struct score_it*) ; 
 struct score_it inst ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct score_it*,struct score_it*,int) ; 
 int my_get_expression (TYPE_4__*,char**) ; 
 int /*<<< orphan*/  nopic_need_relax (scalar_t__,int) ; 
 int nor1 ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_machine_dependent ; 
 TYPE_3__* score_ldst_insns ; 
 scalar_t__ score_pic ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int validate_immediate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_macro_ldst_label (char *str)
{
  int i;
  int ldst_gp_p = 0;
  int reg_rd;
  int r1_bak;
  char *backup_str;
  char *label_str;
  char *absolute_value;
  char append_str[3][MAX_LITERAL_POOL_SIZE];
  char verifystr[MAX_LITERAL_POOL_SIZE];
  struct score_it inst_backup;
  struct score_it inst_expand[3];
  struct score_it inst_main;

  memcpy (&inst_backup, &inst, sizeof (struct score_it));
  strcpy (verifystr, str);
  backup_str = verifystr;

  skip_whitespace (backup_str);
  if ((reg_rd = reg_required_here (&backup_str, -1, REG_TYPE_SCORE)) == (int) FAIL)
    return;

  if (skip_past_comma (&backup_str) == (int) FAIL)
    return;

  label_str = backup_str;

  /* Ld/st rD, [rA, imm]      ld/st rD, [rA]+, imm      ld/st rD, [rA, imm]+.  */
  if (*backup_str == '[')
    {
      inst.type = Rd_rvalueRs_preSI12;
      do_ldst_insn (str);
      return;
    }

  /* Ld/st rD, imm.  */
  absolute_value = backup_str;
  inst.type = Rd_rvalueRs_SI15;
  if ((my_get_expression (&inst.reloc.exp, &backup_str) == (int) FAIL)
      || (validate_immediate (inst.reloc.exp.X_add_number, _VALUE, 0) == (int) FAIL)
      || (end_of_line (backup_str) == (int) FAIL))
    {
      return;
    }
  else
    {
      if (inst.reloc.exp.X_add_symbol == 0)
        {
          memcpy (&inst, &inst_backup, sizeof (struct score_it));
          exp_macro_ldst_abs (str);
          return;
        }
    }

  /* Ld/st rD, label.  */
  inst.type = Rd_rvalueRs_SI15;
  backup_str = absolute_value;
  if ((data_op2 (&backup_str, 1, _GP_IMM15) == (int) FAIL)
      || (end_of_line (backup_str) == (int) FAIL))
    {
      return;
    }
  else
    {
      if (inst.reloc.exp.X_add_symbol == 0)
        {
          if (!inst.error)
	    inst.error = BAD_ARGS;

          return;
        }

      if (score_pic == PIC)
        {
          int ldst_idx = 0;
          ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
          build_lwst_pic (reg_rd, inst.reloc.exp, score_ldst_insns[ldst_idx * 3 + 0].template);
          return;
        }
      else
	{
          if ((inst.reloc.exp.X_add_number <= 0x3fff)
               && (inst.reloc.exp.X_add_number >= -0x4000)
               && (!nopic_need_relax (inst.reloc.exp.X_add_symbol, 1)))
	    {
              int ldst_idx = 0;

              /* Assign the real opcode.  */
              ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
              inst.instruction &= ~OPC_PSEUDOLDST_MASK;
              inst.instruction |= score_ldst_insns[ldst_idx * 3 + 0].value;
              inst.instruction |= reg_rd << 20;
              inst.instruction |= GP << 15;
              inst.relax_inst = 0x8000;
              inst.relax_size = 0;
              ldst_gp_p = 1;
	    }
	}
    }

  /* Backup inst.  */
  memcpy (&inst_main, &inst, sizeof (struct score_it));
  r1_bak = nor1;
  nor1 = 0;

  /* Determine which instructions should be output.  */
  sprintf (append_str[0], "ld_i32hi r1, %s", label_str);
  sprintf (append_str[1], "ld_i32lo r1, %s", label_str);
  sprintf (append_str[2], "%s r%d, [r1, 0]", inst_backup.name, reg_rd);

  /* Generate three instructions.
     la r1, label
     ld/st rd, [r1, 0]  */
  for (i = 0; i < 3; i++)
    {
      if (append_insn (append_str[i], FALSE) == (int) FAIL)
	return;

      memcpy (&inst_expand[i], &inst, sizeof (struct score_it));
    }

  if (ldst_gp_p)
    {
      char *p;

      /* Adjust instruction opcode and to be relaxed instruction opcode.  */
      inst_main.instruction = adjust_paritybit (inst_main.instruction, GET_INSN_CLASS (inst_main.type));
      inst_main.relax_size = inst_expand[0].size + inst_expand[1].size + inst_expand[2].size;
      inst_main.type = Insn_GP;

      for (i = 0; i < 3; i++)
	inst_expand[i].instruction = adjust_paritybit (inst_expand[i].instruction
						       , GET_INSN_CLASS (inst_expand[i].type));

      /* Check data dependency.  */
      handle_dependency (&inst_main);

      /* Start a new frag if frag_now is not empty.  */
      if (frag_now_fix () != 0)
        {
          if (!frag_now->tc_frag_data.is_insn)
	    frag_wane (frag_now);

          frag_new (0);
        }
      frag_grow (20);

      /* Write fr_fix part.  */
      p = frag_more (inst_main.size);
      md_number_to_chars (p, inst_main.instruction, inst_main.size);

      if (inst_main.reloc.type != BFD_RELOC_NONE)
        {
          fix_new_score (frag_now, p - frag_now->fr_literal, inst_main.size,
                         &inst_main.reloc.exp, inst_main.reloc.pc_rel, inst_main.reloc.type);
        }

#ifdef OBJ_ELF
      dwarf2_emit_insn (inst_main.size);
#endif

      /* GP instruction can not do optimization, only can do relax between
         1 instruction and 3 instructions.  */
      p = frag_var (rs_machine_dependent, inst_main.relax_size + RELAX_PAD_BYTE, 0,
                    RELAX_ENCODE (inst_main.size, inst_main.relax_size, inst_main.type, 0, 4, 0),
                    inst_main.reloc.exp.X_add_symbol, 0, NULL);

      /* Write fr_var part.
         no calling gen_insn_frag, no fixS will be generated.  */
      md_number_to_chars (p, inst_expand[0].instruction, inst_expand[0].size);
      p += inst_expand[0].size;
      md_number_to_chars (p, inst_expand[1].instruction, inst_expand[1].size);
      p += inst_expand[1].size;
      md_number_to_chars (p, inst_expand[2].instruction, inst_expand[2].size);
    }
  else
    {
      gen_insn_frag (&inst_expand[0], NULL);
      gen_insn_frag (&inst_expand[1], NULL);
      gen_insn_frag (&inst_expand[2], NULL);
    }
  nor1 = r1_bak;

  /* Set bwarn as -1, so macro instruction itself will not be generated frag.  */
  inst.bwarn = -1;
}