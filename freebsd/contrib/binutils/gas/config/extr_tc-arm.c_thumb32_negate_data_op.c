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
typedef  int offsetT ;

/* Variables and functions */
 unsigned int FAIL ; 
 int T2_DATA_OP_SHIFT ; 
#define  T2_OPCODE_ADC 135 
#define  T2_OPCODE_ADD 134 
#define  T2_OPCODE_AND 133 
#define  T2_OPCODE_BIC 132 
 int T2_OPCODE_MASK ; 
#define  T2_OPCODE_ORN 131 
#define  T2_OPCODE_ORR 130 
#define  T2_OPCODE_SBC 129 
#define  T2_OPCODE_SUB 128 
 unsigned int encode_thumb32_immediate (unsigned int) ; 

__attribute__((used)) static unsigned int
thumb32_negate_data_op (offsetT *instruction, unsigned int value)
{
  int op, new_inst;
  int rd;
  unsigned int negated, inverted;

  negated = encode_thumb32_immediate (-value);
  inverted = encode_thumb32_immediate (~value);

  rd = (*instruction >> 8) & 0xf;
  op = (*instruction >> T2_DATA_OP_SHIFT) & 0xf;
  switch (op)
    {
      /* ADD <-> SUB.  Includes CMP <-> CMN.  */
    case T2_OPCODE_SUB:
      new_inst = T2_OPCODE_ADD;
      value = negated;
      break;

    case T2_OPCODE_ADD:
      new_inst = T2_OPCODE_SUB;
      value = negated;
      break;

      /* ORR <-> ORN.  Includes MOV <-> MVN.  */
    case T2_OPCODE_ORR:
      new_inst = T2_OPCODE_ORN;
      value = inverted;
      break;

    case T2_OPCODE_ORN:
      new_inst = T2_OPCODE_ORR;
      value = inverted;
      break;

      /* AND <-> BIC.  TST has no inverted equivalent.  */
    case T2_OPCODE_AND:
      new_inst = T2_OPCODE_BIC;
      if (rd == 15)
	value = FAIL;
      else
	value = inverted;
      break;

    case T2_OPCODE_BIC:
      new_inst = T2_OPCODE_AND;
      value = inverted;
      break;

      /* ADC <-> SBC  */
    case T2_OPCODE_ADC:
      new_inst = T2_OPCODE_SBC;
      value = inverted;
      break;

    case T2_OPCODE_SBC:
      new_inst = T2_OPCODE_ADC;
      value = inverted;
      break;

      /* We cannot do anything.	 */
    default:
      return FAIL;
    }

  if (value == (unsigned int)FAIL)
    return FAIL;

  *instruction &= T2_OPCODE_MASK;
  *instruction |= new_inst << T2_DATA_OP_SHIFT;
  return value;
}