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
typedef  enum score_insn_type { ____Placeholder_score_insn_type } score_insn_type ;
typedef  enum insn_class { ____Placeholder_insn_class } insn_class ;

/* Variables and functions */
 scalar_t__ FAIL ; 
#define  I15 181 
#define  I5_Rs_Rs_I5_OP5 180 
 int INSN_CLASS_16 ; 
 int INSN_CLASS_32 ; 
 int INSN_CLASS_PCE ; 
 int INSN_CLASS_SYN ; 
#define  Insn_GP 179 
#define  Insn_PIC 178 
#define  Insn_Type_PCE 177 
#define  Insn_Type_SYN 176 
#define  Insn_internal 175 
#define  NO16_OPD 174 
#define  NO_OPD 173 
#define  OP5_rvalueRs_SI15 172 
#define  PC_DISP11div2 171 
#define  PC_DISP19div2 170 
#define  PC_DISP24div2 169 
#define  PC_DISP8div2 168 
#define  Rd_HighRs 167 
#define  Rd_I16 166 
#define  Rd_I4 165 
#define  Rd_I5 164 
#define  Rd_I8 163 
#define  Rd_LowRs 162 
#define  Rd_Rs 161 
#define  Rd_Rs_I14 160 
#define  Rd_Rs_I5 159 
#define  Rd_Rs_Rs 158 
#define  Rd_Rs_Rs_imm 157 
#define  Rd_Rs_SI14 156 
#define  Rd_Rs_x 155 
#define  Rd_SI16 154 
#define  Rd_lvalue32Rs 153 
#define  Rd_lvalueBP_I5 152 
#define  Rd_lvalueRs 151 
#define  Rd_lvalueRs_SI10 150 
#define  Rd_lvalueRs_SI15 149 
#define  Rd_lvalueRs_post4 148 
#define  Rd_lvalueRs_postSI12 147 
#define  Rd_lvalueRs_preSI12 146 
#define  Rd_rvalue32Rs 145 
#define  Rd_rvalueBP_I5 144 
#define  Rd_rvalueRs 143 
#define  Rd_rvalueRs_SI10 142 
#define  Rd_rvalueRs_SI15 141 
#define  Rd_rvalueRs_post4 140 
#define  Rd_rvalueRs_postSI12 139 
#define  Rd_rvalueRs_preSI12 138 
#define  Rd_x_I5 137 
#define  Rd_x_Rs 136 
#define  Rd_x_x 135 
 int /*<<< orphan*/  abort () ; 
#define  x_I5_x 134 
#define  x_Rs 133 
#define  x_Rs_I5 132 
#define  x_Rs_Rs 131 
#define  x_Rs_x 130 
#define  x_lvalueRs_post4 129 
#define  x_rvalueRs_post4 128 

__attribute__((used)) static enum insn_class
get_insn_class_from_type (enum score_insn_type type)
{
  enum insn_class retval = (int) FAIL;

  switch (type)
    {
    case Rd_I4:
    case Rd_I5:
    case Rd_rvalueBP_I5:
    case Rd_lvalueBP_I5:
    case Rd_I8:
    case PC_DISP8div2:
    case PC_DISP11div2:
    case Rd_Rs:
    case Rd_HighRs:
    case Rd_lvalueRs:
    case Rd_rvalueRs:
    case x_Rs:
    case Rd_LowRs:
    case NO16_OPD:
      retval = INSN_CLASS_16;
      break;
    case Rd_Rs_I5:
    case x_Rs_I5:
    case x_I5_x:
    case Rd_Rs_I14:
    case I15:
    case Rd_I16:
    case Rd_SI16:
    case Rd_rvalueRs_SI10:
    case Rd_lvalueRs_SI10:
    case Rd_rvalueRs_preSI12:
    case Rd_rvalueRs_postSI12:
    case Rd_lvalueRs_preSI12:
    case Rd_lvalueRs_postSI12:
    case Rd_Rs_SI14:
    case Rd_rvalueRs_SI15:
    case Rd_lvalueRs_SI15:
    case PC_DISP19div2:
    case PC_DISP24div2:
    case Rd_Rs_Rs:
    case x_Rs_x:
    case x_Rs_Rs:
    case Rd_Rs_x:
    case Rd_x_Rs:
    case Rd_x_x:
    case OP5_rvalueRs_SI15:
    case I5_Rs_Rs_I5_OP5:
    case x_rvalueRs_post4:
    case Rd_rvalueRs_post4:
    case Rd_x_I5:
    case Rd_lvalueRs_post4:
    case x_lvalueRs_post4:
    case Rd_Rs_Rs_imm:
    case NO_OPD:
    case Rd_lvalue32Rs:
    case Rd_rvalue32Rs:
    case Insn_GP:
    case Insn_PIC:
    case Insn_internal:
      retval = INSN_CLASS_32;
      break;
    case Insn_Type_PCE:
      retval = INSN_CLASS_PCE;
      break;
    case Insn_Type_SYN:
      retval = INSN_CLASS_SYN;
      break;
    default:
      abort ();
      break;
    }
  return retval;
}