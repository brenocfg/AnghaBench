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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int GET_MODE_CLASS (int) ; 
 int GET_MODE_INNER (int) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
#define  MODE_FLOAT 131 
#define  MODE_INT 130 
#define  MODE_VECTOR_FLOAT 129 
#define  MODE_VECTOR_INT 128 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_consttable_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_consttable_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
dump_constants_1 (enum machine_mode mode, rtx value, rtx insn)
{
  switch (GET_MODE_CLASS (mode))
    {
    case MODE_INT:
      {
	rtx size = GEN_INT (GET_MODE_SIZE (mode));
	return emit_insn_after (gen_consttable_int (value, size), insn);
      }

    case MODE_FLOAT:
      return emit_insn_after (gen_consttable_float (value), insn);

    case MODE_VECTOR_FLOAT:
    case MODE_VECTOR_INT:
      {
	int i;
	for (i = 0; i < CONST_VECTOR_NUNITS (value); i++)
	  insn = dump_constants_1 (GET_MODE_INNER (mode),
				   CONST_VECTOR_ELT (value, i), insn);
	return insn;
      }

    default:
      gcc_unreachable ();
    }
}