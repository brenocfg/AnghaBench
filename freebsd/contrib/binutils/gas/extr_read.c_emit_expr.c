#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int valueT ;
struct broken_word {char* word_goes_here; scalar_t__ addnum; scalar_t__ use_jump; scalar_t__ added; int /*<<< orphan*/  sub; int /*<<< orphan*/  add; scalar_t__ dispfrag; TYPE_3__* frag; int /*<<< orphan*/  subseg; scalar_t__ seg; struct broken_word* next_broken_word; } ;
typedef  scalar_t__ operatorT ;
struct TYPE_11__ {scalar_t__ X_op; int X_add_number; scalar_t__ X_unsigned; int /*<<< orphan*/  X_op_symbol; int /*<<< orphan*/  X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
struct TYPE_12__ {int fr_literal; } ;
typedef  unsigned long LITTLENUM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_16 ; 
 int /*<<< orphan*/  BFD_RELOC_32 ; 
 int /*<<< orphan*/  BFD_RELOC_64 ; 
 int /*<<< orphan*/  BFD_RELOC_8 ; 
 unsigned int BITS_PER_CHAR ; 
 unsigned int CHARS_PER_LITTLENUM ; 
 unsigned long LITTLENUM_MASK ; 
 unsigned long LITTLENUM_NUMBER_OF_BITS ; 
 scalar_t__ O_absent ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_illegal ; 
 scalar_t__ O_register ; 
 scalar_t__ O_subtract ; 
 scalar_t__ O_uminus ; 
 int /*<<< orphan*/  TC_CONS_FIX_NEW (TYPE_3__*,char*,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned int abs_section_offset ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,...) ; 
 struct broken_word* broken_words ; 
 scalar_t__ check_eh_frame (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  convert_to_bignum (TYPE_1__*) ; 
 int /*<<< orphan*/  dot_value ; 
 int dwarf_file_string ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_3__*,char*,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* frag_more (int) ; 
 TYPE_3__* frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
 unsigned long* generic_bignum ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  listing_source_line (unsigned int) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ need_pass_2 ; 
 int /*<<< orphan*/  new_broken_words ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/  segment_name (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* symbol_get_value_expression (int /*<<< orphan*/ ) ; 
 scalar_t__ target_big_endian ; 
 scalar_t__ xmalloc (int) ; 

void
emit_expr (expressionS *exp, unsigned int nbytes)
{
  operatorT op;
  register char *p;
  valueT extra_digit = 0;

  /* Don't do anything if we are going to make another pass.  */
  if (need_pass_2)
    return;

  dot_value = frag_now_fix ();

#ifndef NO_LISTING
#ifdef OBJ_ELF
  /* When gcc emits DWARF 1 debugging pseudo-ops, a line number will
     appear as a four byte positive constant in the .line section,
     followed by a 2 byte 0xffff.  Look for that case here.  */
  {
    static int dwarf_line = -1;

    if (strcmp (segment_name (now_seg), ".line") != 0)
      dwarf_line = -1;
    else if (dwarf_line >= 0
	     && nbytes == 2
	     && exp->X_op == O_constant
	     && (exp->X_add_number == -1 || exp->X_add_number == 0xffff))
      listing_source_line ((unsigned int) dwarf_line);
    else if (nbytes == 4
	     && exp->X_op == O_constant
	     && exp->X_add_number >= 0)
      dwarf_line = exp->X_add_number;
    else
      dwarf_line = -1;
  }

  /* When gcc emits DWARF 1 debugging pseudo-ops, a file name will
     appear as a 2 byte TAG_compile_unit (0x11) followed by a 2 byte
     AT_sibling (0x12) followed by a four byte address of the sibling
     followed by a 2 byte AT_name (0x38) followed by the name of the
     file.  We look for that case here.  */
  {
    static int dwarf_file = 0;

    if (strcmp (segment_name (now_seg), ".debug") != 0)
      dwarf_file = 0;
    else if (dwarf_file == 0
	     && nbytes == 2
	     && exp->X_op == O_constant
	     && exp->X_add_number == 0x11)
      dwarf_file = 1;
    else if (dwarf_file == 1
	     && nbytes == 2
	     && exp->X_op == O_constant
	     && exp->X_add_number == 0x12)
      dwarf_file = 2;
    else if (dwarf_file == 2
	     && nbytes == 4)
      dwarf_file = 3;
    else if (dwarf_file == 3
	     && nbytes == 2
	     && exp->X_op == O_constant
	     && exp->X_add_number == 0x38)
      dwarf_file = 4;
    else
      dwarf_file = 0;

    /* The variable dwarf_file_string tells stringer that the string
       may be the name of the source file.  */
    if (dwarf_file == 4)
      dwarf_file_string = 1;
    else
      dwarf_file_string = 0;
  }
#endif
#endif

  if (check_eh_frame (exp, &nbytes))
    return;

  op = exp->X_op;

  /* Allow `.word 0' in the absolute section.  */
  if (now_seg == absolute_section)
    {
      if (op != O_constant || exp->X_add_number != 0)
	as_bad (_("attempt to store value in absolute section"));
      abs_section_offset += nbytes;
      return;
    }

  /* Handle a negative bignum.  */
  if (op == O_uminus
      && exp->X_add_number == 0
      && symbol_get_value_expression (exp->X_add_symbol)->X_op == O_big
      && symbol_get_value_expression (exp->X_add_symbol)->X_add_number > 0)
    {
      int i;
      unsigned long carry;

      exp = symbol_get_value_expression (exp->X_add_symbol);

      /* Negate the bignum: one's complement each digit and add 1.  */
      carry = 1;
      for (i = 0; i < exp->X_add_number; i++)
	{
	  unsigned long next;

	  next = (((~(generic_bignum[i] & LITTLENUM_MASK))
		   & LITTLENUM_MASK)
		  + carry);
	  generic_bignum[i] = next & LITTLENUM_MASK;
	  carry = next >> LITTLENUM_NUMBER_OF_BITS;
	}

      /* We can ignore any carry out, because it will be handled by
	 extra_digit if it is needed.  */

      extra_digit = (valueT) -1;
      op = O_big;
    }

  if (op == O_absent || op == O_illegal)
    {
      as_warn (_("zero assumed for missing expression"));
      exp->X_add_number = 0;
      op = O_constant;
    }
  else if (op == O_big && exp->X_add_number <= 0)
    {
      as_bad (_("floating point number invalid"));
      exp->X_add_number = 0;
      op = O_constant;
    }
  else if (op == O_register)
    {
      as_warn (_("register value used as expression"));
      op = O_constant;
    }

  p = frag_more ((int) nbytes);

#ifndef WORKING_DOT_WORD
  /* If we have the difference of two symbols in a word, save it on
     the broken_words list.  See the code in write.c.  */
  if (op == O_subtract && nbytes == 2)
    {
      struct broken_word *x;

      x = (struct broken_word *) xmalloc (sizeof (struct broken_word));
      x->next_broken_word = broken_words;
      broken_words = x;
      x->seg = now_seg;
      x->subseg = now_subseg;
      x->frag = frag_now;
      x->word_goes_here = p;
      x->dispfrag = 0;
      x->add = exp->X_add_symbol;
      x->sub = exp->X_op_symbol;
      x->addnum = exp->X_add_number;
      x->added = 0;
      x->use_jump = 0;
      new_broken_words++;
      return;
    }
#endif

  /* If we have an integer, but the number of bytes is too large to
     pass to md_number_to_chars, handle it as a bignum.  */
  if (op == O_constant && nbytes > sizeof (valueT))
    {
      extra_digit = exp->X_unsigned ? 0 : -1;
      convert_to_bignum (exp);
      op = O_big;
    }

  if (op == O_constant)
    {
      register valueT get;
      register valueT use;
      register valueT mask;
      valueT hibit;
      register valueT unmask;

      /* JF << of >= number of bits in the object is undefined.  In
	 particular SPARC (Sun 4) has problems.  */
      if (nbytes >= sizeof (valueT))
	{
	  mask = 0;
	  if (nbytes > sizeof (valueT))
	    hibit = 0;
	  else
	    hibit = (valueT) 1 << (nbytes * BITS_PER_CHAR - 1);
	}
      else
	{
	  /* Don't store these bits.  */
	  mask = ~(valueT) 0 << (BITS_PER_CHAR * nbytes);
	  hibit = (valueT) 1 << (nbytes * BITS_PER_CHAR - 1);
	}

      unmask = ~mask;		/* Do store these bits.  */

#ifdef NEVER
      "Do this mod if you want every overflow check to assume SIGNED 2's complement data.";
      mask = ~(unmask >> 1);	/* Includes sign bit now.  */
#endif

      get = exp->X_add_number;
      use = get & unmask;
      if ((get & mask) != 0
	  && ((get & mask) != mask
	      || (get & hibit) == 0))
	{		/* Leading bits contain both 0s & 1s.  */
	  as_warn (_("value 0x%lx truncated to 0x%lx"),
		   (unsigned long) get, (unsigned long) use);
	}
      /* Put bytes in right order.  */
      md_number_to_chars (p, use, (int) nbytes);
    }
  else if (op == O_big)
    {
      unsigned int size;
      LITTLENUM_TYPE *nums;

      size = exp->X_add_number * CHARS_PER_LITTLENUM;
      if (nbytes < size)
	{
	  int i = nbytes / CHARS_PER_LITTLENUM;
	  if (i != 0)
	    {
	      LITTLENUM_TYPE sign = 0;
	      if ((generic_bignum[--i]
		   & (1 << (LITTLENUM_NUMBER_OF_BITS - 1))) != 0)
		sign = ~(LITTLENUM_TYPE) 0;
	      while (++i < exp->X_add_number)
		if (generic_bignum[i] != sign)
		  break;
	    }
	  if (i < exp->X_add_number)
	    as_warn (_("bignum truncated to %d bytes"), nbytes);
	  size = nbytes;
	}

      if (nbytes == 1)
	{
	  md_number_to_chars (p, (valueT) generic_bignum[0], 1);
	  return;
	}
      know (nbytes % CHARS_PER_LITTLENUM == 0);

      if (target_big_endian)
	{
	  while (nbytes > size)
	    {
	      md_number_to_chars (p, extra_digit, CHARS_PER_LITTLENUM);
	      nbytes -= CHARS_PER_LITTLENUM;
	      p += CHARS_PER_LITTLENUM;
	    }

	  nums = generic_bignum + size / CHARS_PER_LITTLENUM;
	  while (size >= CHARS_PER_LITTLENUM)
	    {
	      --nums;
	      md_number_to_chars (p, (valueT) *nums, CHARS_PER_LITTLENUM);
	      size -= CHARS_PER_LITTLENUM;
	      p += CHARS_PER_LITTLENUM;
	    }
	}
      else
	{
	  nums = generic_bignum;
	  while (size >= CHARS_PER_LITTLENUM)
	    {
	      md_number_to_chars (p, (valueT) *nums, CHARS_PER_LITTLENUM);
	      ++nums;
	      size -= CHARS_PER_LITTLENUM;
	      p += CHARS_PER_LITTLENUM;
	      nbytes -= CHARS_PER_LITTLENUM;
	    }

	  while (nbytes >= CHARS_PER_LITTLENUM)
	    {
	      md_number_to_chars (p, extra_digit, CHARS_PER_LITTLENUM);
	      nbytes -= CHARS_PER_LITTLENUM;
	      p += CHARS_PER_LITTLENUM;
	    }
	}
    }
  else
    {
      memset (p, 0, nbytes);

      /* Now we need to generate a fixS to record the symbol value.  */

#ifdef TC_CONS_FIX_NEW
      TC_CONS_FIX_NEW (frag_now, p - frag_now->fr_literal, nbytes, exp);
#else
      {
	bfd_reloc_code_real_type r;

	switch (nbytes)
	  {
	  case 1:
	    r = BFD_RELOC_8;
	    break;
	  case 2:
	    r = BFD_RELOC_16;
	    break;
	  case 4:
	    r = BFD_RELOC_32;
	    break;
	  case 8:
	    r = BFD_RELOC_64;
	    break;
	  default:
	    as_bad (_("unsupported BFD relocation size %u"), nbytes);
	    r = BFD_RELOC_32;
	    break;
	  }
	fix_new_exp (frag_now, p - frag_now->fr_literal, (int) nbytes, exp,
		     0, r);
      }
#endif
    }
}