#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct alpha_operand {int flags; scalar_t__ default_reloc; scalar_t__ bits; } ;
struct alpha_opcode {unsigned int opcode; unsigned char* operands; int /*<<< orphan*/  name; } ;
struct alpha_insn {scalar_t__ nfixups; unsigned int insn; struct alpha_fixup* fixups; } ;
struct TYPE_6__ {int X_op; int X_unsigned; int /*<<< orphan*/  X_add_number; } ;
struct alpha_fixup {scalar_t__ reloc; TYPE_2__ exp; } ;
struct TYPE_5__ {scalar_t__ bitsize; } ;
typedef  TYPE_1__ reloc_howto_type ;
typedef  TYPE_2__ expressionS ;
typedef  scalar_t__ bfd_reloc_code_real_type ;

/* Variables and functions */
#define  AXP_OPERAND_DEFAULT_FIRST 134 
#define  AXP_OPERAND_DEFAULT_SECOND 133 
#define  AXP_OPERAND_DEFAULT_ZERO 132 
 int AXP_OPERAND_FAKE ; 
 int AXP_OPERAND_OPTIONAL_MASK ; 
 scalar_t__ BFD_RELOC_ALPHA_GPDISP ; 
 scalar_t__ BFD_RELOC_ALPHA_GPDISP_HI16 ; 
 scalar_t__ BFD_RELOC_ALPHA_GPDISP_LO16 ; 
 scalar_t__ BFD_RELOC_ALPHA_HINT ; 
 scalar_t__ BFD_RELOC_UNUSED ; 
 scalar_t__ MAX_INSN_FIXUPS ; 
 int O_absent ; 
#define  O_constant 131 
#define  O_cpregister 130 
#define  O_pregister 129 
#define  O_register 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 struct alpha_operand* alpha_operands ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_reloc_type_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int insert_operand (unsigned int,struct alpha_operand const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct alpha_insn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
assemble_insn (const struct alpha_opcode *opcode,
	       const expressionS *tok,
	       int ntok,
	       struct alpha_insn *insn,
	       bfd_reloc_code_real_type reloc)
{
  const struct alpha_operand *reloc_operand = NULL;
  const expressionS *reloc_exp = NULL;
  const unsigned char *argidx;
  unsigned image;
  int tokidx = 0;

  memset (insn, 0, sizeof (*insn));
  image = opcode->opcode;

  for (argidx = opcode->operands; *argidx; ++argidx)
    {
      const struct alpha_operand *operand = &alpha_operands[*argidx];
      const expressionS *t = (const expressionS *) 0;

      if (operand->flags & AXP_OPERAND_FAKE)
	{
	  /* Fake operands take no value and generate no fixup.  */
	  image = insert_operand (image, operand, 0, NULL, 0);
	  continue;
	}

      if (tokidx >= ntok)
	{
	  switch (operand->flags & AXP_OPERAND_OPTIONAL_MASK)
	    {
	    case AXP_OPERAND_DEFAULT_FIRST:
	      t = &tok[0];
	      break;
	    case AXP_OPERAND_DEFAULT_SECOND:
	      t = &tok[1];
	      break;
	    case AXP_OPERAND_DEFAULT_ZERO:
	      {
		static expressionS zero_exp;
		t = &zero_exp;
		zero_exp.X_op = O_constant;
		zero_exp.X_unsigned = 1;
	      }
	      break;
	    default:
	      abort ();
	    }
	}
      else
	t = &tok[tokidx++];

      switch (t->X_op)
	{
	case O_register:
	case O_pregister:
	case O_cpregister:
	  image = insert_operand (image, operand, regno (t->X_add_number),
				  NULL, 0);
	  break;

	case O_constant:
	  image = insert_operand (image, operand, t->X_add_number, NULL, 0);
	  assert (reloc_operand == NULL);
	  reloc_operand = operand;
	  reloc_exp = t;
	  break;

	default:
	  /* This is only 0 for fields that should contain registers,
	     which means this pattern shouldn't have matched.  */
	  if (operand->default_reloc == 0)
	    abort ();

	  /* There is one special case for which an insn receives two
	     relocations, and thus the user-supplied reloc does not
	     override the operand reloc.  */
	  if (operand->default_reloc == BFD_RELOC_ALPHA_HINT)
	    {
	      struct alpha_fixup *fixup;

	      if (insn->nfixups >= MAX_INSN_FIXUPS)
		as_fatal (_("too many fixups"));

	      fixup = &insn->fixups[insn->nfixups++];
	      fixup->exp = *t;
	      fixup->reloc = BFD_RELOC_ALPHA_HINT;
	    }
	  else
	    {
	      if (reloc == BFD_RELOC_UNUSED)
		reloc = operand->default_reloc;

	      assert (reloc_operand == NULL);
	      reloc_operand = operand;
	      reloc_exp = t;
	    }
	  break;
	}
    }

  if (reloc != BFD_RELOC_UNUSED)
    {
      struct alpha_fixup *fixup;

      if (insn->nfixups >= MAX_INSN_FIXUPS)
	as_fatal (_("too many fixups"));

      /* ??? My but this is hacky.  But the OSF/1 assembler uses the same
	 relocation tag for both ldah and lda with gpdisp.  Choose the
	 correct internal relocation based on the opcode.  */
      if (reloc == BFD_RELOC_ALPHA_GPDISP)
	{
	  if (strcmp (opcode->name, "ldah") == 0)
	    reloc = BFD_RELOC_ALPHA_GPDISP_HI16;
	  else if (strcmp (opcode->name, "lda") == 0)
	    reloc = BFD_RELOC_ALPHA_GPDISP_LO16;
	  else
	    as_bad (_("invalid relocation for instruction"));
	}

      /* If this is a real relocation (as opposed to a lituse hint), then
	 the relocation width should match the operand width.  */
      else if (reloc < BFD_RELOC_UNUSED)
	{
	  reloc_howto_type *reloc_howto
	    = bfd_reloc_type_lookup (stdoutput, reloc);
	  if (reloc_howto->bitsize != reloc_operand->bits)
	    {
	      as_bad (_("invalid relocation for field"));
	      return;
	    }
	}

      fixup = &insn->fixups[insn->nfixups++];
      if (reloc_exp)
	fixup->exp = *reloc_exp;
      else
	fixup->exp.X_op = O_absent;
      fixup->reloc = reloc;
    }

  insn->insn = image;
}