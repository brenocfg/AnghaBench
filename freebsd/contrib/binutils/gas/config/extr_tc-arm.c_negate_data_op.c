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

/* Variables and functions */
 unsigned long DATA_OP_SHIFT ; 
 int FAIL ; 
#define  OPCODE_ADC 137 
#define  OPCODE_ADD 136 
#define  OPCODE_AND 135 
#define  OPCODE_BIC 134 
#define  OPCODE_CMN 133 
#define  OPCODE_CMP 132 
 unsigned long OPCODE_MASK ; 
#define  OPCODE_MOV 131 
#define  OPCODE_MVN 130 
#define  OPCODE_SBC 129 
#define  OPCODE_SUB 128 
 unsigned long encode_arm_immediate (unsigned long) ; 

__attribute__((used)) static int
negate_data_op (unsigned long * instruction,
		unsigned long	value)
{
  int op, new_inst;
  unsigned long negated, inverted;

  negated = encode_arm_immediate (-value);
  inverted = encode_arm_immediate (~value);

  op = (*instruction >> DATA_OP_SHIFT) & 0xf;
  switch (op)
    {
      /* First negates.	 */
    case OPCODE_SUB:		 /* ADD <-> SUB	 */
      new_inst = OPCODE_ADD;
      value = negated;
      break;

    case OPCODE_ADD:
      new_inst = OPCODE_SUB;
      value = negated;
      break;

    case OPCODE_CMP:		 /* CMP <-> CMN	 */
      new_inst = OPCODE_CMN;
      value = negated;
      break;

    case OPCODE_CMN:
      new_inst = OPCODE_CMP;
      value = negated;
      break;

      /* Now Inverted ops.  */
    case OPCODE_MOV:		 /* MOV <-> MVN	 */
      new_inst = OPCODE_MVN;
      value = inverted;
      break;

    case OPCODE_MVN:
      new_inst = OPCODE_MOV;
      value = inverted;
      break;

    case OPCODE_AND:		 /* AND <-> BIC	 */
      new_inst = OPCODE_BIC;
      value = inverted;
      break;

    case OPCODE_BIC:
      new_inst = OPCODE_AND;
      value = inverted;
      break;

    case OPCODE_ADC:		  /* ADC <-> SBC  */
      new_inst = OPCODE_SBC;
      value = inverted;
      break;

    case OPCODE_SBC:
      new_inst = OPCODE_ADC;
      value = inverted;
      break;

      /* We cannot do anything.	 */
    default:
      return FAIL;
    }

  if (value == (unsigned) FAIL)
    return FAIL;

  *instruction &= OPCODE_MASK;
  *instruction |= new_inst << DATA_OP_SHIFT;
  return value;
}