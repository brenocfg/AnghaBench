#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  subsegT ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_6__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_8__ {char* next_free; } ;
struct TYPE_7__ {int hadone; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_STAB_SECTION (int /*<<< orphan*/ ) ; 
#define  N_SLINE 130 
#define  N_SO 129 
#define  N_SOL 128 
 int /*<<< orphan*/  OBJ_PROCESS_STAB (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  O_symbol ; 
 int SEC_DEBUGGING ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 scalar_t__ SEPARATE_STAB_SECTIONS ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cons (int) ; 
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 char* frag_more (int) ; 
 int /*<<< orphan*/ * frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_absolute_expression () ; 
 char get_absolute_expression_and_terminator (long*) ; 
 unsigned int get_stab_string_offset (char*,char*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__ listing ; 
 int /*<<< orphan*/  listing_source_file (char*) ; 
 int /*<<< orphan*/  listing_source_line (unsigned int) ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ notes ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/  obstack_free (TYPE_3__*,char*) ; 
 TYPE_2__* seg_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symbol_temp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
s_stab_generic (int what, char *stab_secname, char *stabstr_secname)
{
  long longint;
  char *string, *saved_string_obstack_end;
  int type;
  int other;
  int desc;

  /* The general format is:
     .stabs "STRING",TYPE,OTHER,DESC,VALUE
     .stabn TYPE,OTHER,DESC,VALUE
     .stabd TYPE,OTHER,DESC
     At this point input_line_pointer points after the pseudo-op and
     any trailing whitespace.  The argument what is one of 's', 'n' or
     'd' indicating which type of .stab this is.  */

  if (what != 's')
    {
      string = "";
      saved_string_obstack_end = 0;
    }
  else
    {
      int length;

      string = demand_copy_C_string (&length);
      /* FIXME: We should probably find some other temporary storage
	 for string, rather than leaking memory if someone else
	 happens to use the notes obstack.  */
      saved_string_obstack_end = notes.next_free;
      SKIP_WHITESPACE ();
      if (*input_line_pointer == ',')
	input_line_pointer++;
      else
	{
	  as_warn (_(".stab%c: missing comma"), what);
	  ignore_rest_of_line ();
	  return;
	}
    }

  if (get_absolute_expression_and_terminator (&longint) != ',')
    {
      as_warn (_(".stab%c: missing comma"), what);
      ignore_rest_of_line ();
      return;
    }
  type = longint;

  if (get_absolute_expression_and_terminator (&longint) != ',')
    {
      as_warn (_(".stab%c: missing comma"), what);
      ignore_rest_of_line ();
      return;
    }
  other = longint;

  desc = get_absolute_expression ();

  if ((desc > 0xffff) || (desc < -0x8000))
    /* This could happen for example with a source file with a huge
       number of lines.  The only cure is to use a different debug
       format, probably DWARF.  */
    as_warn (_(".stab%c: description field '%x' too big, try a different debug format"),
	     what, desc);

  if (what == 's' || what == 'n')
    {
      if (*input_line_pointer != ',')
	{
	  as_warn (_(".stab%c: missing comma"), what);
	  ignore_rest_of_line ();
	  return;
	}
      input_line_pointer++;
      SKIP_WHITESPACE ();
    }

#ifdef TC_PPC
#ifdef OBJ_ELF
  /* Solaris on PowerPC has decided that .stabd can take 4 arguments, so if we were
     given 4 arguments, make it a .stabn */
  else if (what == 'd')
    {
      char *save_location = input_line_pointer;

      SKIP_WHITESPACE ();
      if (*input_line_pointer == ',')
	{
	  input_line_pointer++;
	  what = 'n';
	}
      else
	input_line_pointer = save_location;
    }
#endif /* OBJ_ELF */
#endif /* TC_PPC */

#ifndef NO_LISTING
  if (listing)
    {
      switch (type)
	{
	case N_SLINE:
	  listing_source_line ((unsigned int) desc);
	  break;
	case N_SO:
	case N_SOL:
	  listing_source_file (string);
	  break;
	}
    }
#endif /* ! NO_LISTING */

  /* We have now gathered the type, other, and desc information.  For
     .stabs or .stabn, input_line_pointer is now pointing at the
     value.  */

  if (SEPARATE_STAB_SECTIONS)
    /* Output the stab information in a separate section.  This is used
       at least for COFF and ELF.  */
    {
      segT saved_seg = now_seg;
      subsegT saved_subseg = now_subseg;
      fragS *saved_frag = frag_now;
      valueT dot;
      segT seg;
      unsigned int stroff;
      char *p;

      static segT cached_sec;
      static char *cached_secname;

      dot = frag_now_fix ();

#ifdef md_flush_pending_output
      md_flush_pending_output ();
#endif

      if (cached_secname && !strcmp (cached_secname, stab_secname))
	{
	  seg = cached_sec;
	  subseg_set (seg, 0);
	}
      else
	{
	  seg = subseg_new (stab_secname, 0);
	  if (cached_secname)
	    free (cached_secname);
	  cached_secname = xstrdup (stab_secname);
	  cached_sec = seg;
	}

      if (! seg_info (seg)->hadone)
	{
	  bfd_set_section_flags (stdoutput, seg,
				 SEC_READONLY | SEC_RELOC | SEC_DEBUGGING);
#ifdef INIT_STAB_SECTION
	  INIT_STAB_SECTION (seg);
#endif
	  seg_info (seg)->hadone = 1;
	}

      stroff = get_stab_string_offset (string, stabstr_secname);
      if (what == 's')
	{
	  /* Release the string, if nobody else has used the obstack.  */
	  if (saved_string_obstack_end == notes.next_free)
	    obstack_free (&notes, string);
	}

      /* At least for now, stabs in a special stab section are always
	 output as 12 byte blocks of information.  */
      p = frag_more (8);
      md_number_to_chars (p, (valueT) stroff, 4);
      md_number_to_chars (p + 4, (valueT) type, 1);
      md_number_to_chars (p + 5, (valueT) other, 1);
      md_number_to_chars (p + 6, (valueT) desc, 2);

      if (what == 's' || what == 'n')
	{
	  /* Pick up the value from the input line.  */
	  cons (4);
	  input_line_pointer--;
	}
      else
	{
	  symbolS *symbol;
	  expressionS exp;

	  /* Arrange for a value representing the current location.  */
	  symbol = symbol_temp_new (saved_seg, dot, saved_frag);

	  exp.X_op = O_symbol;
	  exp.X_add_symbol = symbol;
	  exp.X_add_number = 0;

	  emit_expr (&exp, 4);
	}

#ifdef OBJ_PROCESS_STAB
      OBJ_PROCESS_STAB (seg, what, string, type, other, desc);
#endif

      subseg_set (saved_seg, saved_subseg);
    }
  else
    {
#ifdef OBJ_PROCESS_STAB
      OBJ_PROCESS_STAB (0, what, string, type, other, desc);
#else
      abort ();
#endif
    }

  demand_empty_rest_of_line ();
}