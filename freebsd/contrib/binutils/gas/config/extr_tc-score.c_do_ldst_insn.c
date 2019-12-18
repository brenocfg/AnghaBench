#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ X_op; int /*<<< orphan*/  X_add_number; } ;
struct TYPE_6__ {scalar_t__ pc_rel; TYPE_4__ exp; } ;
struct TYPE_10__ {int instruction; char* error; int relax_inst; int relax_size; TYPE_1__ reloc; } ;
struct TYPE_8__ {int bits; int* range; } ;
struct TYPE_7__ {int value; } ;

/* Variables and functions */
 char* BAD_ARGS ; 
 scalar_t__ FAIL ; 
 int INSN16_LBU ; 
 int INSN16_LH ; 
 int INSN16_LW ; 
 int INSN16_SB ; 
 int INSN16_SH ; 
 int INSN16_SW ; 
 unsigned int INSN_LB ; 
 unsigned int INSN_LBU ; 
 unsigned int INSN_LH ; 
 unsigned int INSN_LHU ; 
 unsigned int INSN_LW ; 
 int INSN_SB ; 
 int INSN_SH ; 
 int INSN_SW ; 
 int LDST_NOUPDATE ; 
 int LDST_POST ; 
 int OPC_PSEUDOLDST_MASK ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  SET_INSN_ERROR (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS ; 
 char* _ (char*) ; 
 unsigned int _IMM10_RSHIFT_2 ; 
 unsigned int _IMM14 ; 
 unsigned int _IMM15 ; 
 unsigned int _IMM16 ; 
 unsigned int _IMM4 ; 
 unsigned int _IMM5 ; 
 unsigned int _IMM5_RSHIFT_1 ; 
 unsigned int _IMM5_RSHIFT_2 ; 
 unsigned int _IMM8 ; 
 size_t _SIMM12 ; 
 unsigned int _SIMM14_NEG ; 
 unsigned int _SIMM15 ; 
 unsigned int _SIMM16_LA ; 
 unsigned int _VALUE_HI16 ; 
 unsigned int _VALUE_LO16 ; 
 int end_of_line (char*) ; 
 char* err_msg ; 
 int exp_ldst_offset (char**,int,size_t) ; 
 TYPE_5__ inst ; 
 int my_get_expression (TYPE_4__*,char**) ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* score_df_range ; 
 TYPE_2__* score_ldst_insns ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 int validate_immediate (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_ldst_insn (char *str)
{
  int pre_inc = 0;
  int conflict_reg;
  int value;
  char * temp;
  char *strbak;
  char *dataptr;
  int reg;
  int ldst_idx = 0;

  strbak = str;
  skip_whitespace (str);

  if (((conflict_reg = reg_required_here (&str, 20, REG_TYPE_SCORE)) == (int) FAIL)
      || (skip_past_comma (&str) == (int) FAIL))
    return;

  /* ld/sw rD, [rA, simm15]    ld/sw rD, [rA]+, simm12     ld/sw rD, [rA, simm12]+.  */
  if (*str == '[')
    {
      str++;
      skip_whitespace (str);

      if ((reg = reg_required_here (&str, 15, REG_TYPE_SCORE)) == (int) FAIL)
	return;

      /* Conflicts can occur on stores as well as loads.  */
      conflict_reg = (conflict_reg == reg);
      skip_whitespace (str);
      temp = str + 1;    /* The latter will process decimal/hex expression.  */

      /* ld/sw rD, [rA]+, simm12    ld/sw rD, [rA]+.  */
      if (*str == ']')
        {
          str++;
          if (*str == '+')
            {
              str++;
              /* ld/sw rD, [rA]+, simm12.  */
              if (skip_past_comma (&str) == SUCCESS)
                {
                  if ((exp_ldst_offset (&str, 3, _SIMM12) == (int) FAIL)
                      || (end_of_line (str) == (int) FAIL))
		    return;

                  if (conflict_reg)
                    {
                      unsigned int ldst_func = inst.instruction & OPC_PSEUDOLDST_MASK;

                      if ((ldst_func == INSN_LH)
                          || (ldst_func == INSN_LHU)
                          || (ldst_func == INSN_LW)
                          || (ldst_func == INSN_LB)
                          || (ldst_func == INSN_LBU))
                        {
                          inst.error = _("register same as write-back base");
                          return;
                        }
                    }

                  ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
                  inst.instruction &= ~OPC_PSEUDOLDST_MASK;
                  inst.instruction |= score_ldst_insns[ldst_idx * 3 + LDST_POST].value;

                  /* lw rD, [rA]+, 4 convert to pop rD, [rA].  */
                  if ((inst.instruction & 0x3e000007) == 0x0e000000)
                    {
                      /* rs =  r0-r7, offset = 4 */
                      if ((((inst.instruction >> 15) & 0x18) == 0)
                          && (((inst.instruction >> 3) & 0xfff) == 4))
                        {
                          /* Relax to pophi.  */
                          if ((((inst.instruction >> 20) & 0x10) == 0x10))
                            {
                              inst.relax_inst = 0x0000200a | (((inst.instruction >> 20) & 0xf)
                                                              << 8) | 1 << 7 |
                                (((inst.instruction >> 15) & 0x7) << 4);
                            }
                          /* Relax to pop.  */
                          else
                            {
                              inst.relax_inst = 0x0000200a | (((inst.instruction >> 20) & 0xf)
                                                              << 8) | 0 << 7 |
                                (((inst.instruction >> 15) & 0x7) << 4);
                            }
                          inst.relax_size = 2;
                        }
                    }
                  return;
                }
              /* ld/sw rD, [rA]+ convert to ld/sw rD, [rA, 0]+.  */
              else
                {
                  SET_INSN_ERROR (NULL);
                  if (end_of_line (str) == (int) FAIL)
                    {
                      return;
                    }

                  pre_inc = 1;
                  value = validate_immediate (inst.reloc.exp.X_add_number, _SIMM12, 0);
                  value &= (1 << score_df_range[_SIMM12].bits) - 1;
                  ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
                  inst.instruction &= ~OPC_PSEUDOLDST_MASK;
                  inst.instruction |= score_ldst_insns[ldst_idx * 3 + pre_inc].value;
                  inst.instruction |= value << 3;
                  inst.relax_inst = 0x8000;
                  return;
                }
            }
          /* ld/sw rD, [rA] convert to ld/sw rD, [rA, simm15].  */
          else
            {
              if (end_of_line (str) == (int) FAIL)
		return;

              ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
              inst.instruction &= ~OPC_PSEUDOLDST_MASK;
              inst.instruction |= score_ldst_insns[ldst_idx * 3 + LDST_NOUPDATE].value;

              /* lbu rd, [rs] -> lbu! rd, [rs]  */
              if (ldst_idx == INSN_LBU)
                {
                  inst.relax_inst = INSN16_LBU;
                }
              else if (ldst_idx == INSN_LH)
                {
                  inst.relax_inst = INSN16_LH;
                }
              else if (ldst_idx == INSN_LW)
                {
                  inst.relax_inst = INSN16_LW;
                }
              else if (ldst_idx == INSN_SB)
                {
                  inst.relax_inst = INSN16_SB;
                }
              else if (ldst_idx == INSN_SH)
                {
                  inst.relax_inst = INSN16_SH;
                }
              else if (ldst_idx == INSN_SW)
                {
                  inst.relax_inst = INSN16_SW;
                }
              else
                {
                  inst.relax_inst = 0x8000;
                }

              /* lw/lh/lbu/sw/sh/sb, offset = 0, relax to 16 bit instruction.  */
              if ((ldst_idx == INSN_LBU)
                  || (ldst_idx == INSN_LH)
                  || (ldst_idx == INSN_LW)
                  || (ldst_idx == INSN_SB) || (ldst_idx == INSN_SH) || (ldst_idx == INSN_SW))
                {
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      inst.relax_inst |= (2 << 12) | (((inst.instruction >> 20) & 0xf) << 8) |
                        (((inst.instruction >> 15) & 0xf) << 4);
                      inst.relax_size = 2;
                    }
                }

              return;
            }
        }
      /* ld/sw rD, [rA, simm15]    ld/sw rD, [rA, simm12]+.  */
      else
        {
          if (skip_past_comma (&str) == (int) FAIL)
            {
              inst.error = _("pre-indexed expression expected");
              return;
            }

          if (my_get_expression (&inst.reloc.exp, &str) == (int) FAIL)
	    return;

          skip_whitespace (str);
          if (*str++ != ']')
            {
              inst.error = _("missing ]");
              return;
            }

          skip_whitespace (str);
          /* ld/sw rD, [rA, simm12]+.  */
          if (*str == '+')
            {
              str++;
              pre_inc = 1;
              if (conflict_reg)
                {
                  unsigned int ldst_func = inst.instruction & OPC_PSEUDOLDST_MASK;

                  if ((ldst_func == INSN_LH)
                      || (ldst_func == INSN_LHU)
                      || (ldst_func == INSN_LW)
                      || (ldst_func == INSN_LB)
                      || (ldst_func == INSN_LBU))
                    {
                      inst.error = _("register same as write-back base");
                      return;
                    }
                }
            }

          if (end_of_line (str) == (int) FAIL)
	    return;

          if (inst.reloc.exp.X_op == O_constant)
            {
              int value;
              unsigned int data_type;

              if (pre_inc == 1)
                data_type = _SIMM12;
              else
                data_type = _SIMM15;
              dataptr = temp;

              if ((*dataptr == '0') && (*(dataptr + 1) == 'x')
                  && (data_type != _SIMM16_LA)
                  && (data_type != _VALUE_HI16)
                  && (data_type != _VALUE_LO16)
                  && (data_type != _IMM16)
                  && (data_type != _IMM15)
                  && (data_type != _IMM14)
                  && (data_type != _IMM4)
                  && (data_type != _IMM5)
                  && (data_type != _IMM8)
                  && (data_type != _IMM5_RSHIFT_1)
                  && (data_type != _IMM5_RSHIFT_2)
                  && (data_type != _SIMM14_NEG)
                  && (data_type != _IMM10_RSHIFT_2))
                {
                  data_type += 24;
                }

              value = validate_immediate (inst.reloc.exp.X_add_number, data_type, 0);
              if (value == (int) FAIL)
                {
                  if (data_type < 30)
                    sprintf (err_msg,
                             _("invalid constant: %d bit expression not in range %d..%d"),
                             score_df_range[data_type].bits,
                             score_df_range[data_type].range[0], score_df_range[data_type].range[1]);
                  else
                    sprintf (err_msg,
                             _("invalid constant: %d bit expression not in range %d..%d"),
                             score_df_range[data_type - 24].bits,
                             score_df_range[data_type - 24].range[0],
                             score_df_range[data_type - 24].range[1]);
                  inst.error = err_msg;
                  return;
                }

              value &= (1 << score_df_range[data_type].bits) - 1;
              ldst_idx = inst.instruction & OPC_PSEUDOLDST_MASK;
              inst.instruction &= ~OPC_PSEUDOLDST_MASK;
              inst.instruction |= score_ldst_insns[ldst_idx * 3 + pre_inc].value;
              if (pre_inc == 1)
                inst.instruction |= value << 3;
              else
                inst.instruction |= value;

              /* lw rD, [rA, simm15]  */
              if ((inst.instruction & 0x3e000000) == 0x20000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0)
                      && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, lw -> lw!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, lw -> lwp!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x3) == 0)
                               && ((inst.instruction & 0x7fff) < 128))
                        {
                          inst.relax_inst = 0x7000 | (((inst.instruction >> 20) & 0xf) << 8)
                            | (((inst.instruction & 0x7fff) >> 2) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* sw rD, [rA, simm15]  */
              else if ((inst.instruction & 0x3e000000) == 0x28000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, sw -> sw!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, sw -> swp!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x3) == 0)
                               && ((inst.instruction & 0x7fff) < 128))
                        {
                          inst.relax_inst = 0x7004 | (((inst.instruction >> 20) & 0xf) << 8)
                            | (((inst.instruction & 0x7fff) >> 2) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* sw rD, [rA, simm15]+    sw pre.  */
              else if ((inst.instruction & 0x3e000007) == 0x06000004)
                {
                  /* rA is in [r0 - r7], and simm15 = -4.  */
                  if ((((inst.instruction >> 15) & 0x18) == 0)
                      && (((inst.instruction >> 3) & 0xfff) == 0xffc))
                    {
                      /* sw -> pushhi!.  */
                      if ((((inst.instruction >> 20) & 0x10) == 0x10))
                        {
                          inst.relax_inst = 0x0000200e | (((inst.instruction >> 20) & 0xf) << 8)
                            | 1 << 7 | (((inst.instruction >> 15) & 0x7) << 4);
                          inst.relax_size = 2;
                        }
                      /* sw -> push!.  */
                      else
                        {
                          inst.relax_inst = 0x0000200e | (((inst.instruction >> 20) & 0xf) << 8)
                            | 0 << 7 | (((inst.instruction >> 15) & 0x7) << 4);
                          inst.relax_size = 2;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* lh rD, [rA, simm15]  */
              else if ((inst.instruction & 0x3e000000) == 0x22000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, lh -> lh!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, lh -> lhp!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x1) == 0)
                               && ((inst.instruction & 0x7fff) < 64))
                        {
                          inst.relax_inst = 0x7001 | (((inst.instruction >> 20) & 0xf) << 8)
                            | (((inst.instruction & 0x7fff) >> 1) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* sh rD, [rA, simm15]  */
              else if ((inst.instruction & 0x3e000000) == 0x2a000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, sh -> sh!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, sh -> shp!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x1) == 0)
                               && ((inst.instruction & 0x7fff) < 64))
                        {
                          inst.relax_inst = 0x7005 | (((inst.instruction >> 20) & 0xf) << 8)
                            | (((inst.instruction & 0x7fff) >> 1) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* lbu rD, [rA, simm15]  */
              else if ((inst.instruction & 0x3e000000) == 0x2c000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, lbu -> lbu!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, lbu -> lbup!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x7fff) < 32))
                        {
                          inst.relax_inst = 0x7003 | (((inst.instruction >> 20) & 0xf) << 8)
                            | ((inst.instruction & 0x7fff) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              /* sb rD, [rA, simm15]  */
              else if ((inst.instruction & 0x3e000000) == 0x2e000000)
                {
                  /* Both rD and rA are in [r0 - r15].  */
                  if ((((inst.instruction >> 15) & 0x10) == 0) && (((inst.instruction >> 20) & 0x10) == 0))
                    {
                      /* simm15 = 0, sb -> sb!.  */
                      if ((inst.instruction & 0x7fff) == 0)
                        {
                          inst.relax_inst |= (((inst.instruction >> 15) & 0xf) << 4)
                            | (((inst.instruction >> 20) & 0xf) << 8);
                          inst.relax_size = 2;
                        }
                      /* rA = r2, sb -> sb!.  */
                      else if ((((inst.instruction >> 15) & 0xf) == 2)
                               && ((inst.instruction & 0x7fff) < 32))
                        {
                          inst.relax_inst = 0x7007 | (((inst.instruction >> 20) & 0xf) << 8)
                            | ((inst.instruction & 0x7fff) << 3);
                          inst.relax_size = 2;
                        }
                      else
                        {
                          inst.relax_inst = 0x8000;
                        }
                    }
                  else
                    {
                      inst.relax_inst = 0x8000;
                    }
                }
              else
                {
                  inst.relax_inst = 0x8000;
                }

              return;
            }
          else
            {
              /* FIXME: may set error, for there is no ld/sw rD, [rA, label] */
              inst.reloc.pc_rel = 0;
            }
        }
    }
  else
    {
      inst.error = BAD_ARGS;
    }
}