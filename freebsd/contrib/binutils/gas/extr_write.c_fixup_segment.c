#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int valueT ;
typedef  scalar_t__ segT ;
struct TYPE_17__ {int fr_address; } ;
typedef  TYPE_1__ fragS ;
struct TYPE_18__ {int fx_offset; int fx_pcrel; int fx_dot_value; int fx_size; int fx_where; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; scalar_t__ fx_signed; int /*<<< orphan*/  fx_no_overflow; int /*<<< orphan*/  fx_bit_fixP; int /*<<< orphan*/ * fx_subsy; int /*<<< orphan*/ * fx_addsy; int /*<<< orphan*/  fx_done; TYPE_1__* fx_frag; struct TYPE_18__* fx_next; } ;
typedef  TYPE_2__ fixS ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_UNUSED_LABEL ; 
 scalar_t__ MD_APPLY_SYM_VALUE (TYPE_2__*) ; 
 scalar_t__ MD_PCREL_FROM_SECTION (TYPE_2__*,scalar_t__) ; 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TC_ADJUST_RELOC_COUNT (TYPE_2__*,long) ; 
 int /*<<< orphan*/  TC_FORCE_RELOCATION_ABS (TYPE_2__*) ; 
 int /*<<< orphan*/  TC_FORCE_RELOCATION_LOCAL (TYPE_2__*) ; 
 int /*<<< orphan*/  TC_FORCE_RELOCATION_SUB_ABS (TYPE_2__*) ; 
 int /*<<< orphan*/  TC_FORCE_RELOCATION_SUB_LOCAL (TYPE_2__*) ; 
 int /*<<< orphan*/  TC_FORCE_RELOCATION_SUB_SAME (TYPE_2__*,scalar_t__) ; 
 scalar_t__ TC_LINKRELAX_FIXUP (scalar_t__) ; 
 int /*<<< orphan*/  TC_VALIDATE_FIX (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_VALIDATE_FIX_SUB (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * abs_section_sym ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bfd_is_com_section (scalar_t__) ; 
 int /*<<< orphan*/  flag_signed_overflow_ok ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  know (TYPE_1__*) ; 
 scalar_t__ linkrelax ; 
 int /*<<< orphan*/  md_apply_fix (TYPE_2__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  print_fixup (TYPE_2__*) ; 
 int /*<<< orphan*/  resolve_symbol_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * section_symbol (scalar_t__) ; 
 int /*<<< orphan*/  segment_name (scalar_t__) ; 
 int /*<<< orphan*/  skip ; 
 int /*<<< orphan*/  sprint_value (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  symbol_mark_used_in_reloc (int /*<<< orphan*/ *) ; 
 scalar_t__ undefined_section ; 

__attribute__((used)) static long
fixup_segment (fixS *fixP, segT this_segment)
{
  long seg_reloc_count = 0;
  valueT add_number;
  fragS *fragP;
  segT add_symbol_segment = absolute_section;

  if (fixP != NULL && abs_section_sym == NULL)
    abs_section_sym = section_symbol (absolute_section);

  /* If the linker is doing the relaxing, we must not do any fixups.

     Well, strictly speaking that's not true -- we could do any that
     are PC-relative and don't cross regions that could change size.
     And for the i960 we might be able to turn callx/callj into bal
     anyways in cases where we know the maximum displacement.  */
  if (linkrelax && TC_LINKRELAX_FIXUP (this_segment))
    {
      for (; fixP; fixP = fixP->fx_next)
	if (!fixP->fx_done)
	  {
	    if (fixP->fx_addsy == NULL)
	      {
		/* There was no symbol required by this relocation.
		   However, BFD doesn't really handle relocations
		   without symbols well. So fake up a local symbol in
		   the absolute section.  */
		fixP->fx_addsy = abs_section_sym;
	      }
	    symbol_mark_used_in_reloc (fixP->fx_addsy);
	    if (fixP->fx_subsy != NULL)
	      symbol_mark_used_in_reloc (fixP->fx_subsy);
	    seg_reloc_count++;
	  }
      TC_ADJUST_RELOC_COUNT (fixP, seg_reloc_count);
      return seg_reloc_count;
    }

  for (; fixP; fixP = fixP->fx_next)
    {
#ifdef DEBUG5
      fprintf (stderr, "\nprocessing fixup:\n");
      print_fixup (fixP);
#endif

      fragP = fixP->fx_frag;
      know (fragP);
#ifdef TC_VALIDATE_FIX
      TC_VALIDATE_FIX (fixP, this_segment, skip);
#endif
      add_number = fixP->fx_offset;

      if (fixP->fx_addsy != NULL)
	add_symbol_segment = S_GET_SEGMENT (fixP->fx_addsy);

      if (fixP->fx_subsy != NULL)
	{
	  segT sub_symbol_segment;
	  resolve_symbol_value (fixP->fx_subsy);
	  sub_symbol_segment = S_GET_SEGMENT (fixP->fx_subsy);
	  if (fixP->fx_addsy != NULL
	      && sub_symbol_segment == add_symbol_segment
	      && !TC_FORCE_RELOCATION_SUB_SAME (fixP, add_symbol_segment))
	    {
	      add_number += S_GET_VALUE (fixP->fx_addsy);
	      add_number -= S_GET_VALUE (fixP->fx_subsy);
	      fixP->fx_offset = add_number;
	      fixP->fx_addsy = NULL;
	      fixP->fx_subsy = NULL;
#ifdef TC_M68K
	      /* See the comment below about 68k weirdness.  */
	      fixP->fx_pcrel = 0;
#endif
	    }
	  else if (sub_symbol_segment == absolute_section
		   && !TC_FORCE_RELOCATION_SUB_ABS (fixP))
	    {
	      add_number -= S_GET_VALUE (fixP->fx_subsy);
	      fixP->fx_offset = add_number;
	      fixP->fx_subsy = NULL;
	    }
	  else if (sub_symbol_segment == this_segment
		   && !TC_FORCE_RELOCATION_SUB_LOCAL (fixP))
	    {
	      add_number -= S_GET_VALUE (fixP->fx_subsy);
	      fixP->fx_offset = (add_number + fixP->fx_dot_value
				 + fixP->fx_frag->fr_address);

	      /* Make it pc-relative.  If the back-end code has not
		 selected a pc-relative reloc, cancel the adjustment
		 we do later on all pc-relative relocs.  */
	      if (0
#ifdef TC_M68K
		  /* Do this for m68k even if it's already described
		     as pc-relative.  On the m68k, an operand of
		     "pc@(foo-.-2)" should address "foo" in a
		     pc-relative mode.  */
		  || 1
#endif
		  || !fixP->fx_pcrel)
		add_number += MD_PCREL_FROM_SECTION (fixP, this_segment);
	      fixP->fx_subsy = NULL;
	      fixP->fx_pcrel = 1;
	    }
	  else if (!TC_VALIDATE_FIX_SUB (fixP))
	    {
	      as_bad_where (fixP->fx_file, fixP->fx_line,
			    _("can't resolve `%s' {%s section} - `%s' {%s section}"),
			    fixP->fx_addsy ? S_GET_NAME (fixP->fx_addsy) : "0",
			    segment_name (add_symbol_segment),
			    S_GET_NAME (fixP->fx_subsy),
			    segment_name (sub_symbol_segment));
	    }
	}

      if (fixP->fx_addsy)
	{
	  if (add_symbol_segment == this_segment
	      && !TC_FORCE_RELOCATION_LOCAL (fixP))
	    {
	      /* This fixup was made when the symbol's segment was
		 SEG_UNKNOWN, but it is now in the local segment.
		 So we know how to do the address without relocation.  */
	      add_number += S_GET_VALUE (fixP->fx_addsy);
	      fixP->fx_offset = add_number;
	      if (fixP->fx_pcrel)
		add_number -= MD_PCREL_FROM_SECTION (fixP, this_segment);
	      fixP->fx_addsy = NULL;
	      fixP->fx_pcrel = 0;
	    }
	  else if (add_symbol_segment == absolute_section
		   && !TC_FORCE_RELOCATION_ABS (fixP))
	    {
	      add_number += S_GET_VALUE (fixP->fx_addsy);
	      fixP->fx_offset = add_number;
	      fixP->fx_addsy = NULL;
	    }
	  else if (add_symbol_segment != undefined_section
		   && ! bfd_is_com_section (add_symbol_segment)
		   && MD_APPLY_SYM_VALUE (fixP))
	    add_number += S_GET_VALUE (fixP->fx_addsy);
	}

      if (fixP->fx_pcrel)
	{
	  add_number -= MD_PCREL_FROM_SECTION (fixP, this_segment);
	  if (!fixP->fx_done && fixP->fx_addsy == NULL)
	    {
	      /* There was no symbol required by this relocation.
		 However, BFD doesn't really handle relocations
		 without symbols well. So fake up a local symbol in
		 the absolute section.  */
	      fixP->fx_addsy = abs_section_sym;
	    }
	}

      if (!fixP->fx_done)
	md_apply_fix (fixP, &add_number, this_segment);

      if (!fixP->fx_done)
	{
	  ++seg_reloc_count;
	  if (fixP->fx_addsy == NULL)
	    fixP->fx_addsy = abs_section_sym;
	  symbol_mark_used_in_reloc (fixP->fx_addsy);
	  if (fixP->fx_subsy != NULL)
	    symbol_mark_used_in_reloc (fixP->fx_subsy);
	}

      if (!fixP->fx_bit_fixP && !fixP->fx_no_overflow && fixP->fx_size != 0)
	{
	  if (fixP->fx_size < sizeof (valueT))
	    {
	      valueT mask;

	      mask = 0;
	      mask--;		/* Set all bits to one.  */
	      mask <<= fixP->fx_size * 8 - (fixP->fx_signed ? 1 : 0);
	      if ((add_number & mask) != 0 && (add_number & mask) != mask)
		{
		  char buf[50], buf2[50];
		  sprint_value (buf, fragP->fr_address + fixP->fx_where);
		  if (add_number > 1000)
		    sprint_value (buf2, add_number);
		  else
		    sprintf (buf2, "%ld", (long) add_number);
		  as_bad_where (fixP->fx_file, fixP->fx_line,
				_("value of %s too large for field of %d bytes at %s"),
				buf2, fixP->fx_size, buf);
		} /* Generic error checking.  */
	    }
#ifdef WARN_SIGNED_OVERFLOW_WORD
	  /* Warn if a .word value is too large when treated as a signed
	     number.  We already know it is not too negative.  This is to
	     catch over-large switches generated by gcc on the 68k.  */
	  if (!flag_signed_overflow_ok
	      && fixP->fx_size == 2
	      && add_number > 0x7fff)
	    as_bad_where (fixP->fx_file, fixP->fx_line,
			  _("signed .word overflow; switch may be too large; %ld at 0x%lx"),
			  (long) add_number,
			  (long) (fragP->fr_address + fixP->fx_where));
#endif
	}			/* Not a bit fix.  */

#ifdef TC_VALIDATE_FIX
    skip:  ATTRIBUTE_UNUSED_LABEL
      ;
#endif
#ifdef DEBUG5
      fprintf (stderr, "result:\n");
      print_fixup (fixP);
#endif
    }				/* For each fixS in this segment.  */

  TC_ADJUST_RELOC_COUNT (fixP, seg_reloc_count);
  return seg_reloc_count;
}