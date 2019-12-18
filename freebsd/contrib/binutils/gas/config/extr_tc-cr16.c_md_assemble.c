#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  inst ;
struct TYPE_8__ {TYPE_1__* arg; } ;
typedef  TYPE_2__ ins ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ constant; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSPACE (char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ arg_ic ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ assemble_insn (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  check_cinv_options (char*) ; 
 int /*<<< orphan*/  cr16_inst_hash ; 
 int /*<<< orphan*/  dwarf2_emit_insn (int /*<<< orphan*/ ) ; 
 char* get_b_cc (char*) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const* instruction ; 
 scalar_t__ is_bcc_insn (char*) ; 
 int /*<<< orphan*/  parse_insn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  parse_operands (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  print_insn (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_vars (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ streq (char*,char*) ; 

void
md_assemble (char *op)
{
  ins cr16_ins;
  char *param, param1[32];
  char c;

  /* Reset global variables for a new instruction.  */
  reset_vars (op);

  /* Strip the mnemonic.  */
  for (param = op; *param != 0 && !ISSPACE (*param); param++)
    ;
  c = *param;
  *param++ = '\0';

  /* bCC instuctions and adjust the mnemonic by adding extra white spaces.  */
  if (is_bcc_insn (op))
    {
      strcpy (param1, get_b_cc (op));
      op = "b";
      strcat (param1,",");
      strcat (param1, param);
      param = (char *) &param1;
    }

  /* Checking the cinv options and adjust the mnemonic by removing the
     extra white spaces.  */
  if (streq ("cinv", op))
    {
     /* Validate the cinv options.  */
      check_cinv_options (param);
      strcat (op, param);
    }

  /* MAPPING - SHIFT INSN, if imm4/imm16 positive values
     lsh[b/w] imm4/imm6, reg ==> ashu[b/w] imm4/imm16, reg
     as CR16 core doesn't support lsh[b/w] right shift operaions.  */
  if ((streq ("lshb", op) || streq ("lshw", op) || streq ("lshd", op))
      && (param [0] == '$'))
    {
      strcpy (param1, param);
      /* Find the instruction.  */
      instruction = (const inst *) hash_find (cr16_inst_hash, op);
       parse_operands (&cr16_ins, param1);
      if (((&cr16_ins)->arg[0].type == arg_ic)
	  && ((&cr16_ins)->arg[0].constant >= 0))
        {
           if (streq ("lshb", op))
	     op = "ashub";
           else if (streq ("lshd", op))
	     op = "ashud";
	   else
	     op = "ashuw";
        }
    }

  /* Find the instruction.  */
  instruction = (const inst *) hash_find (cr16_inst_hash, op);
  if (instruction == NULL)
    {
      as_bad (_("Unknown opcode: `%s'"), op);
      return;
    }

  /* Tie dwarf2 debug info to the address at the start of the insn.  */
  dwarf2_emit_insn (0);

  /* Parse the instruction's operands.  */
  parse_insn (&cr16_ins, param);

  /* Assemble the instruction - return upon failure.  */
  if (assemble_insn (op, &cr16_ins) == 0)
    return;

  /* Print the instruction.  */
  print_insn (&cr16_ins);
}