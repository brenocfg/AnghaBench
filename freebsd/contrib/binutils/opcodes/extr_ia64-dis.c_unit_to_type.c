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
typedef  int /*<<< orphan*/  ia64_insn ;
typedef  enum ia64_unit { ____Placeholder_ia64_unit } ia64_unit ;
typedef  enum ia64_insn_type { ____Placeholder_ia64_insn_type } ia64_insn_type ;

/* Variables and functions */
 int IA64_OP (int /*<<< orphan*/ ) ; 
 int IA64_TYPE_A ; 
 int IA64_TYPE_B ; 
 int IA64_TYPE_F ; 
 int IA64_TYPE_I ; 
 int IA64_TYPE_M ; 
 int IA64_TYPE_X ; 
#define  IA64_UNIT_B 133 
#define  IA64_UNIT_F 132 
#define  IA64_UNIT_I 131 
#define  IA64_UNIT_L 130 
#define  IA64_UNIT_M 129 
#define  IA64_UNIT_X 128 

__attribute__((used)) static enum ia64_insn_type
unit_to_type (ia64_insn opcode, enum ia64_unit unit)
{
  enum ia64_insn_type type;
  int op;

  op = IA64_OP (opcode);

  if (op >= 8 && (unit == IA64_UNIT_I || unit == IA64_UNIT_M))
    {
      type = IA64_TYPE_A;
    }
  else
    {
      switch (unit)
	{
	case IA64_UNIT_I:
	  type = IA64_TYPE_I; break;
	case IA64_UNIT_M:
	  type = IA64_TYPE_M; break;
	case IA64_UNIT_B:
	  type = IA64_TYPE_B; break;
	case IA64_UNIT_F:
	  type = IA64_TYPE_F; break;
        case IA64_UNIT_L:
	case IA64_UNIT_X:
	  type = IA64_TYPE_X; break;
	default:
	  type = -1;
	}
    }
  return type;
}