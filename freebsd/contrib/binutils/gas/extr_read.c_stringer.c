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
 int /*<<< orphan*/  FRAG_APPEND_1_CHAR (unsigned int) ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  dwarf_file_string ; 
 unsigned int get_single_number () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int* input_line_pointer ; 
 int /*<<< orphan*/  is_a_char (unsigned int) ; 
 scalar_t__ is_it_end_of_statement () ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  listing_source_file (char*) ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 unsigned int next_char_of_string () ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  segment_name (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void
stringer (/* Worker to do .ascii etc statements.  */
	  /* Checks end-of-line.  */
	  register int append_zero	/* 0: don't append '\0', else 1.  */)
{
  register unsigned int c;
  char *start;

#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  /* The following awkward logic is to parse ZERO or more strings,
     comma separated. Recall a string expression includes spaces
     before the opening '\"' and spaces after the closing '\"'.
     We fake a leading ',' if there is (supposed to be)
     a 1st, expression. We keep demanding expressions for each ','.  */
  if (is_it_end_of_statement ())
    {
      c = 0;			/* Skip loop.  */
      ++input_line_pointer;	/* Compensate for end of loop.  */
    }
  else
    {
      c = ',';			/* Do loop.  */
    }
  /* If we have been switched into the abs_section then we
     will not have an obstack onto which we can hang strings.  */
  if (now_seg == absolute_section)
    {
      as_bad (_("strings must be placed into a section"));
      c = 0;
      ignore_rest_of_line ();
    }

  while (c == ',' || c == '<' || c == '"')
    {
      SKIP_WHITESPACE ();
      switch (*input_line_pointer)
	{
	case '\"':
	  ++input_line_pointer;	/*->1st char of string.  */
	  start = input_line_pointer;
	  while (is_a_char (c = next_char_of_string ()))
	    {
	      FRAG_APPEND_1_CHAR (c);
	    }
	  if (append_zero)
	    {
	      FRAG_APPEND_1_CHAR (0);
	    }
	  know (input_line_pointer[-1] == '\"');

#ifndef NO_LISTING
#ifdef OBJ_ELF
	  /* In ELF, when gcc is emitting DWARF 1 debugging output, it
	     will emit .string with a filename in the .debug section
	     after a sequence of constants.  See the comment in
	     emit_expr for the sequence.  emit_expr will set
	     dwarf_file_string to non-zero if this string might be a
	     source file name.  */
	  if (strcmp (segment_name (now_seg), ".debug") != 0)
	    dwarf_file_string = 0;
	  else if (dwarf_file_string)
	    {
	      c = input_line_pointer[-1];
	      input_line_pointer[-1] = '\0';
	      listing_source_file (start);
	      input_line_pointer[-1] = c;
	    }
#endif
#endif

	  break;
	case '<':
	  input_line_pointer++;
	  c = get_single_number ();
	  FRAG_APPEND_1_CHAR (c);
	  if (*input_line_pointer != '>')
	    {
	      as_bad (_("expected <nn>"));
	    }
	  input_line_pointer++;
	  break;
	case ',':
	  input_line_pointer++;
	  break;
	}
      SKIP_WHITESPACE ();
      c = *input_line_pointer;
    }

  demand_empty_rest_of_line ();
}