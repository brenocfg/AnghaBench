#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct arc_operand_value {size_t type; long value; int /*<<< orphan*/  name; } ;
struct arc_operand {int flags; size_t fmt; long (* insert ) (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ;long shift; int bits; } ;
typedef  struct arc_opcode {long value; char* syntax; int flags; } const arc_opcode ;
struct TYPE_9__ {scalar_t__ X_op; long X_add_number; } ;
struct arc_fixup {size_t opindex; TYPE_1__ exp; } ;
typedef  TYPE_1__ expressionS ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  long arc_insn ;
struct TYPE_10__ {char* fr_literal; } ;

/* Variables and functions */
 int ARC_DELAY_NONE ; 
 int ARC_MOD_BITS ; 
 int ARC_MOD_DOT ; 
 scalar_t__ ARC_MOD_P (int) ; 
 int ARC_OPCODE_COND_BRANCH ; 
 struct arc_opcode const* ARC_OPCODE_NEXT_ASM (struct arc_opcode const*) ; 
 int ARC_OPERAND_ABSOLUTE_BRANCH ; 
 int ARC_OPERAND_ADDRESS ; 
 int ARC_OPERAND_ERROR ; 
 int ARC_OPERAND_FAKE ; 
 int ARC_OPERAND_LIMM ; 
 int ARC_OPERAND_RELATIVE_BRANCH ; 
 int ARC_OPERAND_SUFFIX ; 
 int ARC_OPERAND_WARN ; 
 int BFD_RELOC_32 ; 
 int BFD_RELOC_ARC_B26 ; 
 scalar_t__ BFD_RELOC_UNUSED ; 
 scalar_t__ ISALNUM (char) ; 
 scalar_t__ ISSPACE (char) ; 
 scalar_t__ IS_REG_DEST_OPERAND (char) ; 
 scalar_t__ IS_REG_SHIMM_OFFSET (char) ; 
 scalar_t__ IS_SYMBOL_OPERAND (char) ; 
 int MAX_FIXUPS ; 
 int MAX_SUFFIXES ; 
 scalar_t__ O_absent ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_illegal ; 
 scalar_t__ O_register ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arc_code_symbol (TYPE_1__*) ; 
 struct arc_opcode const* arc_ext_opcodes ; 
 scalar_t__ arc_insn_not_jl (long) ; 
 scalar_t__ arc_limm_fixup_adjust (long) ; 
 scalar_t__ arc_mach_type ; 
 int /*<<< orphan*/  arc_opcode_init_insert () ; 
 long arc_opcode_limm_p (long*) ; 
 struct arc_opcode const* arc_opcode_lookup_asm (char*) ; 
 int /*<<< orphan*/  arc_opcode_supported (struct arc_opcode const*) ; 
 size_t* arc_operand_map ; 
 struct arc_operand* arc_operands ; 
 int /*<<< orphan*/  arc_suffix_hash ; 
 struct arc_operand_value* arc_suffixes ; 
 int arc_suffixes_count ; 
 int /*<<< orphan*/  as_bad (char const*,...) ; 
 int /*<<< orphan*/  as_fatal (char*,...) ; 
 int /*<<< orphan*/  as_warn (char const*) ; 
 scalar_t__ bfd_mach_arc_5 ; 
 int /*<<< orphan*/  dwarf2_emit_insn (int) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_4__*,int,int,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 char* frag_more (int) ; 
 TYPE_4__* frag_now ; 
 int get_arc_exp_reloc_type (int,int,TYPE_1__*,TYPE_1__*) ; 
 struct arc_operand_value* get_ext_suffix (char*) ; 
 struct arc_operand_value* hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_opcode_tables (scalar_t__) ; 
 char* input_line_pointer ; 
 scalar_t__* is_end_of_line ; 
 int /*<<< orphan*/  md_number_to_chars (char*,long,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 long stub1 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 
 long stub2 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 
 long stub3 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 
 long stub4 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 
 long stub5 (long,struct arc_operand const*,int,struct arc_operand_value const*,long,char const**) ; 

void
md_assemble (char *str)
{
  const struct arc_opcode *opcode;
  const struct arc_opcode *std_opcode;
  struct arc_opcode *ext_opcode;
  char *start;
  const char *last_errmsg = 0;
  arc_insn insn;
  static int init_tables_p = 0;

  /* Opcode table initialization is deferred until here because we have to
     wait for a possible .option command.  */
  if (!init_tables_p)
    {
      init_opcode_tables (arc_mach_type);
      init_tables_p = 1;
    }

  /* Skip leading white space.  */
  while (ISSPACE (*str))
    str++;

  /* The instructions are stored in lists hashed by the first letter (though
     we needn't care how they're hashed).  Get the first in the list.  */

  ext_opcode = arc_ext_opcodes;
  std_opcode = arc_opcode_lookup_asm (str);

  /* Keep looking until we find a match.  */
  start = str;
  for (opcode = (ext_opcode ? ext_opcode : std_opcode);
       opcode != NULL;
       opcode = (ARC_OPCODE_NEXT_ASM (opcode)
		 ? ARC_OPCODE_NEXT_ASM (opcode)
		 : (ext_opcode ? ext_opcode = NULL, std_opcode : NULL)))
    {
      int past_opcode_p, fc, num_suffixes;
      int fix_up_at = 0;
      char *syn;
      struct arc_fixup fixups[MAX_FIXUPS];
      /* Used as a sanity check.  If we need a limm reloc, make sure we ask
	 for an extra 4 bytes from frag_more.  */
      int limm_reloc_p;
      int ext_suffix_p;
      const struct arc_operand_value *insn_suffixes[MAX_SUFFIXES];

      /* Is this opcode supported by the selected cpu?  */
      if (! arc_opcode_supported (opcode))
	continue;

      /* Scan the syntax string.  If it doesn't match, try the next one.  */
      arc_opcode_init_insert ();
      insn = opcode->value;
      fc = 0;
      past_opcode_p = 0;
      num_suffixes = 0;
      limm_reloc_p = 0;
      ext_suffix_p = 0;

      /* We don't check for (*str != '\0') here because we want to parse
	 any trailing fake arguments in the syntax string.  */
      for (str = start, syn = opcode->syntax; *syn != '\0';)
	{
	  int mods;
	  const struct arc_operand *operand;

	  /* Non operand chars must match exactly.  */
	  if (*syn != '%' || *++syn == '%')
	    {
	     if (*str == *syn)
		{
		  if (*syn == ' ')
		    past_opcode_p = 1;
		  ++syn;
		  ++str;
		}
	      else
		break;
	      continue;
	    }

	  /* We have an operand.  Pick out any modifiers.  */
	  mods = 0;
	  while (ARC_MOD_P (arc_operands[arc_operand_map[(int) *syn]].flags))
	    {
	      mods |= arc_operands[arc_operand_map[(int) *syn]].flags & ARC_MOD_BITS;
	      ++syn;
	    }
	  operand = arc_operands + arc_operand_map[(int) *syn];
	  if (operand->fmt == 0)
	    as_fatal ("unknown syntax format character `%c'", *syn);

	  if (operand->flags & ARC_OPERAND_FAKE)
	    {
	      const char *errmsg = NULL;
	      if (operand->insert)
		{
		  insn = (*operand->insert) (insn, operand, mods, NULL, 0, &errmsg);
		  if (errmsg != (const char *) NULL)
		    {
		      last_errmsg = errmsg;
		      if (operand->flags & ARC_OPERAND_ERROR)
			{
			  as_bad (errmsg);
			  return;
			}
		      else if (operand->flags & ARC_OPERAND_WARN)
			as_warn (errmsg);
		      break;
		    }
		  if (limm_reloc_p
		      && (operand->flags && operand->flags & ARC_OPERAND_LIMM)
		      && (operand->flags &
			  (ARC_OPERAND_ABSOLUTE_BRANCH | ARC_OPERAND_ADDRESS)))
		    {
		      fixups[fix_up_at].opindex = arc_operand_map[operand->fmt];
		    }
		}
	      ++syn;
	    }
	  /* Are we finished with suffixes?  */
	  else if (!past_opcode_p)
	    {
	      int found;
	      char c;
	      char *s, *t;
	      const struct arc_operand_value *suf, *suffix_end;
	      const struct arc_operand_value *suffix = NULL;

	      if (!(operand->flags & ARC_OPERAND_SUFFIX))
		abort ();

	      /* If we're at a space in the input string, we want to skip the
		 remaining suffixes.  There may be some fake ones though, so
		 just go on to try the next one.  */
	      if (*str == ' ')
		{
		  ++syn;
		  continue;
		}

	      s = str;
	      if (mods & ARC_MOD_DOT)
		{
		  if (*s != '.')
		    break;
		  ++s;
		}
	      else
		{
		  /* This can happen in "b.nd foo" and we're currently looking
		     for "%q" (ie: a condition code suffix).  */
		  if (*s == '.')
		    {
		      ++syn;
		      continue;
		    }
		}

	      /* Pick the suffix out and look it up via the hash table.  */
	      for (t = s; *t && ISALNUM (*t); ++t)
		continue;
	      c = *t;
	      *t = '\0';
	      if ((suf = get_ext_suffix (s)))
		ext_suffix_p = 1;
	      else
		suf = hash_find (arc_suffix_hash, s);
	      if (!suf)
		{
		  /* This can happen in "blle foo" and we're currently using
		     the template "b%q%.n %j".  The "bl" insn occurs later in
		     the table so "lle" isn't an illegal suffix.  */
		  *t = c;
		  break;
		}

	      /* Is it the right type?  Note that the same character is used
		 several times, so we have to examine all of them.  This is
		 relatively efficient as equivalent entries are kept
		 together.  If it's not the right type, don't increment `str'
		 so we try the next one in the series.  */
	      found = 0;
	      if (ext_suffix_p && arc_operands[suf->type].fmt == *syn)
		{
		  /* Insert the suffix's value into the insn.  */
		  *t = c;
		  if (operand->insert)
		    insn = (*operand->insert) (insn, operand,
					       mods, NULL, suf->value,
					       NULL);
		  else
		    insn |= suf->value << operand->shift;
		  suffix = suf;
		  str = t;
		  found = 1;
		}
	      else
		{
		  *t = c;
		  suffix_end = arc_suffixes + arc_suffixes_count;
		  for (suffix = suf;
		       suffix < suffix_end && strcmp (suffix->name, suf->name) == 0;
		       ++suffix)
		    {
		      if (arc_operands[suffix->type].fmt == *syn)
			{
			  /* Insert the suffix's value into the insn.  */
			  if (operand->insert)
			    insn = (*operand->insert) (insn, operand,
						       mods, NULL, suffix->value,
						       NULL);
			  else
			    insn |= suffix->value << operand->shift;

			  str = t;
			  found = 1;
			  break;
			}
		    }
		}
	      ++syn;
	      if (!found)
		/* Wrong type.  Just go on to try next insn entry.  */
		;
	      else
		{
		  if (num_suffixes == MAX_SUFFIXES)
		    as_bad ("too many suffixes");
		  else
		    insn_suffixes[num_suffixes++] = suffix;
		}
	    }
	  else
	    /* This is either a register or an expression of some kind.  */
	    {
	      char *hold;
	      const struct arc_operand_value *reg = NULL;
	      long value = 0;
	      expressionS exp;

	      if (operand->flags & ARC_OPERAND_SUFFIX)
		abort ();

	      /* Is there anything left to parse?
		 We don't check for this at the top because we want to parse
		 any trailing fake arguments in the syntax string.  */
	      if (is_end_of_line[(unsigned char) *str])
		break;

	      /* Parse the operand.  */
	      hold = input_line_pointer;
	      input_line_pointer = str;
	      expression (&exp);
	      str = input_line_pointer;
	      input_line_pointer = hold;

	      if (exp.X_op == O_illegal)
		as_bad ("illegal operand");
	      else if (exp.X_op == O_absent)
		as_bad ("missing operand");
	      else if (exp.X_op == O_constant)
		value = exp.X_add_number;
	      else if (exp.X_op == O_register)
		reg = (struct arc_operand_value *) exp.X_add_number;
#define IS_REG_DEST_OPERAND(o) ((o) == 'a')
	      else if (IS_REG_DEST_OPERAND (*syn))
		as_bad ("symbol as destination register");
	      else
		{
		  if (!strncmp (str, "@h30", 4))
		    {
		      arc_code_symbol (&exp);
		      str += 4;
		    }
		  /* We need to generate a fixup for this expression.  */
		  if (fc >= MAX_FIXUPS)
		    as_fatal ("too many fixups");
		  fixups[fc].exp = exp;
		  /* We don't support shimm relocs. break here to force
		     the assembler to output a limm.  */
#define IS_REG_SHIMM_OFFSET(o) ((o) == 'd')
		  if (IS_REG_SHIMM_OFFSET (*syn))
		    break;
		  /* If this is a register constant (IE: one whose
		     register value gets stored as 61-63) then this
		     must be a limm.  */
		  /* ??? This bit could use some cleaning up.
		     Referencing the format chars like this goes
		     against style.  */
		  if (IS_SYMBOL_OPERAND (*syn))
		    {
		      const char *junk;
		      limm_reloc_p = 1;
		      /* Save this, we don't yet know what reloc to use.  */
		      fix_up_at = fc;
		      /* Tell insert_reg we need a limm.  This is
			 needed because the value at this point is
			 zero, a shimm.  */
		      /* ??? We need a cleaner interface than this.  */
		      (*arc_operands[arc_operand_map['Q']].insert)
			(insn, operand, mods, reg, 0L, &junk);
		    }
		  else
		    fixups[fc].opindex = arc_operand_map[(int) *syn];
		  ++fc;
		  value = 0;
		}

	      /* Insert the register or expression into the instruction.  */
	      if (operand->insert)
		{
		  const char *errmsg = NULL;
		  insn = (*operand->insert) (insn, operand, mods,
					     reg, (long) value, &errmsg);
		  if (errmsg != (const char *) NULL)
		    {
		      last_errmsg = errmsg;
		      if (operand->flags & ARC_OPERAND_ERROR)
			{
			  as_bad (errmsg);
			  return;
			}
		      else if (operand->flags & ARC_OPERAND_WARN)
			as_warn (errmsg);
		      break;
		    }
		}
	      else
		insn |= (value & ((1 << operand->bits) - 1)) << operand->shift;

	      ++syn;
	    }
	}

      /* If we're at the end of the syntax string, we're done.  */
      /* FIXME: try to move this to a separate function.  */
      if (*syn == '\0')
	{
	  int i;
	  char *f;
	  long limm, limm_p;

	  /* For the moment we assume a valid `str' can only contain blanks
	     now.  IE: We needn't try again with a longer version of the
	     insn and it is assumed that longer versions of insns appear
	     before shorter ones (eg: lsr r2,r3,1 vs lsr r2,r3).  */

	  while (ISSPACE (*str))
	    ++str;

	  if (!is_end_of_line[(unsigned char) *str])
	    as_bad ("junk at end of line: `%s'", str);

	  /* Is there a limm value?  */
	  limm_p = arc_opcode_limm_p (&limm);

	  /* Perform various error and warning tests.  */

	  {
	    static int in_delay_slot_p = 0;
	    static int prev_insn_needs_cc_nop_p = 0;
	    /* delay slot type seen */
	    int delay_slot_type = ARC_DELAY_NONE;
	    /* conditional execution flag seen */
	    int conditional = 0;
	    /* 1 if condition codes are being set */
	    int cc_set_p = 0;
	    /* 1 if conditional branch, including `b' "branch always" */
	    int cond_branch_p = opcode->flags & ARC_OPCODE_COND_BRANCH;

	    for (i = 0; i < num_suffixes; ++i)
	      {
		switch (arc_operands[insn_suffixes[i]->type].fmt)
		  {
		  case 'n':
		    delay_slot_type = insn_suffixes[i]->value;
		    break;
		  case 'q':
		    conditional = insn_suffixes[i]->value;
		    break;
		  case 'f':
		    cc_set_p = 1;
		    break;
		  }
	      }

	    /* Putting an insn with a limm value in a delay slot is supposed to
	       be legal, but let's warn the user anyway.  Ditto for 8 byte
	       jumps with delay slots.  */
	    if (in_delay_slot_p && limm_p)
	      as_warn ("8 byte instruction in delay slot");
	    if (delay_slot_type != ARC_DELAY_NONE
		&& limm_p && arc_insn_not_jl (insn)) /* except for jl  addr */
	      as_warn ("8 byte jump instruction with delay slot");
	    in_delay_slot_p = (delay_slot_type != ARC_DELAY_NONE) && !limm_p;

	    /* Warn when a conditional branch immediately follows a set of
	       the condition codes.  Note that this needn't be done if the
	       insn that sets the condition codes uses a limm.  */
	    if (cond_branch_p && conditional != 0 /* 0 = "always" */
		&& prev_insn_needs_cc_nop_p && arc_mach_type == bfd_mach_arc_5)
	      as_warn ("conditional branch follows set of flags");
	    prev_insn_needs_cc_nop_p =
	      /* FIXME: ??? not required:
		 (delay_slot_type != ARC_DELAY_NONE) &&  */
	      cc_set_p && !limm_p;
	  }

	  /* Write out the instruction.
	     It is important to fetch enough space in one call to `frag_more'.
	     We use (f - frag_now->fr_literal) to compute where we are and we
	     don't want frag_now to change between calls.  */
	  if (limm_p)
	    {
	      f = frag_more (8);
	      md_number_to_chars (f, insn, 4);
	      md_number_to_chars (f + 4, limm, 4);
	      dwarf2_emit_insn (8);
	    }
	  else if (limm_reloc_p)
	    /* We need a limm reloc, but the tables think we don't.  */
	    abort ();
	  else
	    {
	      f = frag_more (4);
	      md_number_to_chars (f, insn, 4);
	      dwarf2_emit_insn (4);
	    }

	  /* Create any fixups.  */
	  for (i = 0; i < fc; ++i)
	    {
	      int op_type, reloc_type;
	      expressionS exptmp;
	      const struct arc_operand *operand;

	      /* Create a fixup for this operand.
		 At this point we do not use a bfd_reloc_code_real_type for
		 operands residing in the insn, but instead just use the
		 operand index.  This lets us easily handle fixups for any
		 operand type, although that is admittedly not a very exciting
		 feature.  We pick a BFD reloc type in md_apply_fix.

		 Limm values (4 byte immediate "constants") must be treated
		 normally because they're not part of the actual insn word
		 and thus the insertion routines don't handle them.  */

	      if (arc_operands[fixups[i].opindex].flags & ARC_OPERAND_LIMM)
		{
		  /* Modify the fixup addend as required by the cpu.  */
		  fixups[i].exp.X_add_number += arc_limm_fixup_adjust (insn);
		  op_type = fixups[i].opindex;
		  /* FIXME: can we add this data to the operand table?  */
		  if (op_type == arc_operand_map['L']
		      || op_type == arc_operand_map['s']
		      || op_type == arc_operand_map['o']
		      || op_type == arc_operand_map['O'])
		    reloc_type = BFD_RELOC_32;
		  else if (op_type == arc_operand_map['J'])
		    reloc_type = BFD_RELOC_ARC_B26;
		  else
		    abort ();
		  reloc_type = get_arc_exp_reloc_type (1, reloc_type,
						       &fixups[i].exp,
						       &exptmp);
		}
	      else
		{
		  op_type = get_arc_exp_reloc_type (0, fixups[i].opindex,
						    &fixups[i].exp, &exptmp);
		  reloc_type = op_type + (int) BFD_RELOC_UNUSED;
		}
	      operand = &arc_operands[op_type];
	      fix_new_exp (frag_now,
			   ((f - frag_now->fr_literal)
			    + (operand->flags & ARC_OPERAND_LIMM ? 4 : 0)), 4,
			   &exptmp,
			   (operand->flags & ARC_OPERAND_RELATIVE_BRANCH) != 0,
			   (bfd_reloc_code_real_type) reloc_type);
	    }
	  return;
	}
    }

  if (NULL == last_errmsg)
    as_bad ("bad instruction `%s'", start);
  else
    as_bad (last_errmsg);
}