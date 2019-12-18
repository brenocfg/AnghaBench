#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; TYPE_2__* section; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_OBJECT ; 
 int BSF_WEAK ; 
 char TOUPPER (char) ; 
 scalar_t__ bfd_is_abs_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_ind_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_2__*) ; 
 char coff_section_type (int /*<<< orphan*/ ) ; 
 char decode_section_type (TYPE_2__*) ; 

int
bfd_decode_symclass (asymbol *symbol)
{
  char c;

  if (bfd_is_com_section (symbol->section))
    return 'C';
  if (bfd_is_und_section (symbol->section))
    {
      if (symbol->flags & BSF_WEAK)
	{
	  /* If weak, determine if it's specifically an object
	     or non-object weak.  */
	  if (symbol->flags & BSF_OBJECT)
	    return 'v';
	  else
	    return 'w';
	}
      else
	return 'U';
    }
  if (bfd_is_ind_section (symbol->section))
    return 'I';
  if (symbol->flags & BSF_WEAK)
    {
      /* If weak, determine if it's specifically an object
	 or non-object weak.  */
      if (symbol->flags & BSF_OBJECT)
	return 'V';
      else
	return 'W';
    }
  if (!(symbol->flags & (BSF_GLOBAL | BSF_LOCAL)))
    return '?';

  if (bfd_is_abs_section (symbol->section))
    c = 'a';
  else if (symbol->section)
    {
      c = coff_section_type (symbol->section->name);
      if (c == '?')
	c = decode_section_type (symbol->section);
    }
  else
    return '?';
  if (symbol->flags & BSF_GLOBAL)
    c = TOUPPER (c);
  return c;

  /* We don't have to handle these cases just yet, but we will soon:
     N_SETV: 'v';
     N_SETA: 'l';
     N_SETT: 'x';
     N_SETD: 'z';
     N_SETB: 's';
     N_INDR: 'i';
     */
}