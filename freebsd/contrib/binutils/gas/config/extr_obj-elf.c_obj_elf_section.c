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
 int SHF_GROUP ; 
 int SHF_MERGE ; 
 int SHT_NULL ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 scalar_t__ flag_mri ; 
 int get_absolute_expression () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  md_elf_section_change_hook () ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/  obj_elf_change_section (char*,int,int,int,char*,int,int) ; 
 int obj_elf_parse_section_letters (char*,int) ; 
 char* obj_elf_section_name () ; 
 int obj_elf_section_type (char*,int) ; 
 int obj_elf_section_word (char*,int) ; 
 int /*<<< orphan*/  previous_section ; 
 int /*<<< orphan*/  previous_subsection ; 
 int /*<<< orphan*/  s_mri_sect (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
obj_elf_section (int push)
{
  char *name, *group_name, *beg;
  int type, attr, dummy;
  int entsize;
  int linkonce;

#ifndef TC_I370
  if (flag_mri)
    {
      char mri_type;

#ifdef md_flush_pending_output
      md_flush_pending_output ();
#endif

      previous_section = now_seg;
      previous_subsection = now_subseg;

      s_mri_sect (&mri_type);

#ifdef md_elf_section_change_hook
      md_elf_section_change_hook ();
#endif

      return;
    }
#endif /* ! defined (TC_I370) */

  name = obj_elf_section_name ();
  if (name == NULL)
    return;
  type = SHT_NULL;
  attr = 0;
  group_name = NULL;
  entsize = 0;
  linkonce = 0;

  if (*input_line_pointer == ',')
    {
      /* Skip the comma.  */
      ++input_line_pointer;
      SKIP_WHITESPACE ();

      if (*input_line_pointer == '"')
	{
	  beg = demand_copy_C_string (&dummy);
	  if (beg == NULL)
	    {
	      ignore_rest_of_line ();
	      return;
	    }
	  attr |= obj_elf_parse_section_letters (beg, strlen (beg));

	  SKIP_WHITESPACE ();
	  if (*input_line_pointer == ',')
	    {
	      char c;
	      char *save = input_line_pointer;

	      ++input_line_pointer;
	      SKIP_WHITESPACE ();
	      c = *input_line_pointer;
	      if (c == '"')
		{
		  beg = demand_copy_C_string (&dummy);
		  if (beg == NULL)
		    {
		      ignore_rest_of_line ();
		      return;
		    }
		  type = obj_elf_section_type (beg, strlen (beg));
		}
	      else if (c == '@' || c == '%')
		{
		  beg = ++input_line_pointer;
		  c = get_symbol_end ();
		  *input_line_pointer = c;
		  type = obj_elf_section_type (beg, input_line_pointer - beg);
		}
	      else
		input_line_pointer = save;
	    }

	  SKIP_WHITESPACE ();
	  if ((attr & SHF_MERGE) != 0 && *input_line_pointer == ',')
	    {
	      ++input_line_pointer;
	      SKIP_WHITESPACE ();
	      entsize = get_absolute_expression ();
	      SKIP_WHITESPACE ();
	      if (entsize < 0)
		{
		  as_warn (_("invalid merge entity size"));
		  attr &= ~SHF_MERGE;
		  entsize = 0;
		}
	    }
	  else if ((attr & SHF_MERGE) != 0)
	    {
	      as_warn (_("entity size for SHF_MERGE not specified"));
	      attr &= ~SHF_MERGE;
	    }

	  if ((attr & SHF_GROUP) != 0 && *input_line_pointer == ',')
	    {
	      ++input_line_pointer;
	      group_name = obj_elf_section_name ();
	      if (group_name == NULL)
		attr &= ~SHF_GROUP;
	      else if (strncmp (input_line_pointer, ",comdat", 7) == 0)
		{
		  input_line_pointer += 7;
		  linkonce = 1;
		}
	      else if (strncmp (name, ".gnu.linkonce", 13) == 0)
		linkonce = 1;
	    }
	  else if ((attr & SHF_GROUP) != 0)
	    {
	      as_warn (_("group name for SHF_GROUP not specified"));
	      attr &= ~SHF_GROUP;
	    }
	}
      else
	{
	  do
	    {
	      char c;

	      SKIP_WHITESPACE ();
	      if (*input_line_pointer != '#')
		{
		  as_bad (_("character following name is not '#'"));
		  ignore_rest_of_line ();
		  return;
		}
	      beg = ++input_line_pointer;
	      c = get_symbol_end ();
	      *input_line_pointer = c;

	      attr |= obj_elf_section_word (beg, input_line_pointer - beg);

	      SKIP_WHITESPACE ();
	    }
	  while (*input_line_pointer++ == ',');
	  --input_line_pointer;
	}
    }

  demand_empty_rest_of_line ();

  obj_elf_change_section (name, type, attr, entsize, group_name, linkonce, push);
}