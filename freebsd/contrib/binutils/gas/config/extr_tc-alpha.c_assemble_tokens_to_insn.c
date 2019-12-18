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
struct alpha_opcode {int dummy; } ;
struct alpha_insn {int dummy; } ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  alpha_opcode_hash ; 
 int /*<<< orphan*/  alpha_target_name ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  assemble_insn (struct alpha_opcode const*,int /*<<< orphan*/  const*,int,struct alpha_insn*,int /*<<< orphan*/ ) ; 
 struct alpha_opcode* find_opcode_match (struct alpha_opcode const*,int /*<<< orphan*/  const*,int*,int*) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
assemble_tokens_to_insn (const char *opname,
			 const expressionS *tok,
			 int ntok,
			 struct alpha_insn *insn)
{
  const struct alpha_opcode *opcode;

  /* Search opcodes.  */
  opcode = (const struct alpha_opcode *) hash_find (alpha_opcode_hash, opname);
  if (opcode)
    {
      int cpumatch;
      opcode = find_opcode_match (opcode, tok, &ntok, &cpumatch);
      if (opcode)
	{
	  assemble_insn (opcode, tok, ntok, insn, BFD_RELOC_UNUSED);
	  return;
	}
      else if (cpumatch)
	as_bad (_("inappropriate arguments for opcode `%s'"), opname);
      else
	as_bad (_("opcode `%s' not supported for target %s"), opname,
		alpha_target_name);
    }
  else
    as_bad (_("unknown opcode `%s'"), opname);
}