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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {scalar_t__ value; int flags; TYPE_3__* section; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_8__ {scalar_t__ index; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_SECTION_SYM ; 
 scalar_t__ FALSE ; 
 scalar_t__ IEEE_SECTION_NUMBER_BASE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_asymbol_name (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_is_abs_section (TYPE_3__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_3__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_function_minus_enum ; 
 int /*<<< orphan*/  ieee_function_plus_enum ; 
 int /*<<< orphan*/  ieee_variable_I_enum ; 
 int /*<<< orphan*/  ieee_variable_P_enum ; 
 int /*<<< orphan*/  ieee_variable_R_enum ; 
 int /*<<< orphan*/  ieee_variable_X_enum ; 
 int /*<<< orphan*/  ieee_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_int (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfd_boolean
ieee_write_expression (bfd *abfd,
		       bfd_vma value,
		       asymbol *symbol,
		       bfd_boolean pcrel,
		       unsigned int index)
{
  unsigned int term_count = 0;

  if (value != 0)
    {
      if (! ieee_write_int (abfd, value))
	return FALSE;
      term_count++;
    }

  /* Badly formatted binaries can have a missing symbol,
     so test here to prevent a seg fault.  */
  if (symbol != NULL)
    {
      if (bfd_is_com_section (symbol->section)
	  || bfd_is_und_section (symbol->section))
	{
	  /* Def of a common symbol.  */
	  if (! ieee_write_byte (abfd, ieee_variable_X_enum)
	      || ! ieee_write_int (abfd, symbol->value))
	    return FALSE;
	  term_count ++;
	}
      else if (! bfd_is_abs_section (symbol->section))
	{
	  /* Ref to defined symbol -  */
	  if (symbol->flags & BSF_GLOBAL)
	    {
	      if (! ieee_write_byte (abfd, ieee_variable_I_enum)
		  || ! ieee_write_int (abfd, symbol->value))
		return FALSE;
	      term_count++;
	    }
	  else if (symbol->flags & (BSF_LOCAL | BSF_SECTION_SYM))
	    {
	      /* This is a reference to a defined local symbol.  We can
		 easily do a local as a section+offset.  */
	      if (! ieee_write_byte (abfd, ieee_variable_R_enum)
		  || ! ieee_write_byte (abfd,
					(bfd_byte) (symbol->section->index
						    + IEEE_SECTION_NUMBER_BASE)))
		return FALSE;

	      term_count++;
	      if (symbol->value != 0)
		{
		  if (! ieee_write_int (abfd, symbol->value))
		    return FALSE;
		  term_count++;
		}
	    }
	  else
	    {
	      (*_bfd_error_handler)
		(_("%s: unrecognized symbol `%s' flags 0x%x"),
		 bfd_get_filename (abfd), bfd_asymbol_name (symbol),
		 symbol->flags);
	      bfd_set_error (bfd_error_invalid_operation);
	      return FALSE;
	    }
	}
    }

  if (pcrel)
    {
      /* Subtract the pc from here by asking for PC of this section.  */
      if (! ieee_write_byte (abfd, ieee_variable_P_enum)
	  || ! ieee_write_byte (abfd,
				(bfd_byte) (index + IEEE_SECTION_NUMBER_BASE))
	  || ! ieee_write_byte (abfd, ieee_function_minus_enum))
	return FALSE;
    }

  /* Handle the degenerate case of a 0 address.  */
  if (term_count == 0)
    if (! ieee_write_int (abfd, (bfd_vma) 0))
      return FALSE;

  while (term_count > 1)
    {
      if (! ieee_write_byte (abfd, ieee_function_plus_enum))
	return FALSE;
      term_count--;
    }

  return TRUE;
}