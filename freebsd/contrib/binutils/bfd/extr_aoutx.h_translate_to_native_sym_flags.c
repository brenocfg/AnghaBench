#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct external_nlist {int* e_type; int /*<<< orphan*/  e_value; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {int flags; int /*<<< orphan*/ * name; scalar_t__ value; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_17__ {scalar_t__ vma; struct TYPE_17__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_2__ asection ;
struct TYPE_18__ {int type; } ;
typedef  TYPE_3__ aout_symbol_type ;

/* Variables and functions */
 int BSF_CONSTRUCTOR ; 
 int BSF_DEBUGGING ; 
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_WARNING ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
#define  N_ABS 132 
#define  N_BSS 131 
#define  N_DATA 130 
 int N_EXT ; 
 int N_INDR ; 
 int N_SETA ; 
 int N_SETB ; 
 int N_SETD ; 
 int N_SETT ; 
#define  N_TEXT 129 
 int N_TYPE ; 
#define  N_UNDF 128 
 int N_WARNING ; 
 int N_WEAKA ; 
 int N_WEAKB ; 
 int N_WEAKD ; 
 int N_WEAKT ; 
 int N_WEAKU ; 
 int /*<<< orphan*/  PUT_WORD (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ aout_section_merge_with_text_p (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_error_nonrepresentable_section ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 TYPE_2__* bfd_get_section (TYPE_1__*) ; 
 int /*<<< orphan*/ * bfd_get_section_name (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ bfd_is_abs_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_ind_section (TYPE_2__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_2__* obj_bsssec (int /*<<< orphan*/ *) ; 
 TYPE_2__* obj_datasec (int /*<<< orphan*/ *) ; 
 TYPE_2__* obj_textsec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
translate_to_native_sym_flags (bfd *abfd,
			       asymbol *cache_ptr,
			       struct external_nlist *sym_pointer)
{
  bfd_vma value = cache_ptr->value;
  asection *sec;
  bfd_vma off;

  /* Mask out any existing type bits in case copying from one section
     to another.  */
  sym_pointer->e_type[0] &= ~N_TYPE;

  sec = bfd_get_section (cache_ptr);
  off = 0;

  if (sec == NULL)
    {
      /* This case occurs, e.g., for the *DEBUG* section of a COFF
	 file.  */
      (*_bfd_error_handler)
	(_("%s: can not represent section for symbol `%s' in a.out object file format"),
	 bfd_get_filename (abfd),
	 cache_ptr->name != NULL ? cache_ptr->name : _("*unknown*"));
      bfd_set_error (bfd_error_nonrepresentable_section);
      return FALSE;
    }

  if (sec->output_section != NULL)
    {
      off = sec->output_offset;
      sec = sec->output_section;
    }

  if (bfd_is_abs_section (sec))
    sym_pointer->e_type[0] |= N_ABS;
  else if (sec == obj_textsec (abfd))
    sym_pointer->e_type[0] |= N_TEXT;
  else if (sec == obj_datasec (abfd))
    sym_pointer->e_type[0] |= N_DATA;
  else if (sec == obj_bsssec (abfd))
    sym_pointer->e_type[0] |= N_BSS;
  else if (bfd_is_und_section (sec))
    sym_pointer->e_type[0] = N_UNDF | N_EXT;
  else if (bfd_is_ind_section (sec))
    sym_pointer->e_type[0] = N_INDR;
  else if (bfd_is_com_section (sec))
    sym_pointer->e_type[0] = N_UNDF | N_EXT;
  else
    {
      if (aout_section_merge_with_text_p (abfd, sec))
	sym_pointer->e_type[0] |= N_TEXT;
      else
	{
          (*_bfd_error_handler)
	   (_("%s: can not represent section `%s' in a.out object file format"),
	     bfd_get_filename (abfd), bfd_get_section_name (abfd, sec));
          bfd_set_error (bfd_error_nonrepresentable_section);
          return FALSE;
	}
    }

  /* Turn the symbol from section relative to absolute again.  */
  value += sec->vma + off;

  if ((cache_ptr->flags & BSF_WARNING) != 0)
    sym_pointer->e_type[0] = N_WARNING;

  if ((cache_ptr->flags & BSF_DEBUGGING) != 0)
    sym_pointer->e_type[0] = ((aout_symbol_type *) cache_ptr)->type;
  else if ((cache_ptr->flags & BSF_GLOBAL) != 0)
    sym_pointer->e_type[0] |= N_EXT;
  else if ((cache_ptr->flags & BSF_LOCAL) != 0)
    sym_pointer->e_type[0] &= ~N_EXT;

  if ((cache_ptr->flags & BSF_CONSTRUCTOR) != 0)
    {
      int type = ((aout_symbol_type *) cache_ptr)->type;

      switch (type)
	{
	case N_ABS:	type = N_SETA; break;
	case N_TEXT:	type = N_SETT; break;
	case N_DATA:	type = N_SETD; break;
	case N_BSS:	type = N_SETB; break;
	}
      sym_pointer->e_type[0] = type;
    }

  if ((cache_ptr->flags & BSF_WEAK) != 0)
    {
      int type;

      switch (sym_pointer->e_type[0] & N_TYPE)
	{
	default:
	case N_ABS:	type = N_WEAKA; break;
	case N_TEXT:	type = N_WEAKT; break;
	case N_DATA:	type = N_WEAKD; break;
	case N_BSS:	type = N_WEAKB; break;
	case N_UNDF:	type = N_WEAKU; break;
	}
      sym_pointer->e_type[0] = type;
    }

  PUT_WORD (abfd, value, sym_pointer->e_value);

  return TRUE;
}