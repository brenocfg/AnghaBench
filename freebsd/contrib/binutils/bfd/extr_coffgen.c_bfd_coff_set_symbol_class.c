#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {unsigned int n_sclass; int /*<<< orphan*/  n_flags; scalar_t__ n_value; void* n_scnum; int /*<<< orphan*/  n_type; } ;
struct TYPE_18__ {TYPE_2__ syment; } ;
struct TYPE_19__ {TYPE_3__ u; } ;
typedef  TYPE_4__ combined_entry_type ;
struct TYPE_20__ {TYPE_4__* native; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_5__ coff_symbol_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_21__ {TYPE_10__* section; scalar_t__ value; } ;
typedef  TYPE_6__ asymbol ;
struct TYPE_16__ {scalar_t__ vma; void* target_index; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {TYPE_1__* output_section; scalar_t__ output_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* N_UNDEF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  T_NULL ; 
 TYPE_13__* bfd_asymbol_bfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_is_com_section (TYPE_10__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_10__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_4__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* coff_symbol_from (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  obj_pe (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_coff_set_symbol_class (bfd *         abfd,
			   asymbol *     symbol,
			   unsigned int  class)
{
  coff_symbol_type * csym;

  csym = coff_symbol_from (abfd, symbol);
  if (csym == NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }
  else if (csym->native == NULL)
    {
      /* This is an alien symbol which no native coff backend data.
	 We cheat here by creating a fake native entry for it and
	 then filling in the class.  This code is based on that in
	 coff_write_alien_symbol().  */

      combined_entry_type * native;
      bfd_size_type amt = sizeof (* native);

      native = bfd_zalloc (abfd, amt);
      if (native == NULL)
	return FALSE;

      native->u.syment.n_type   = T_NULL;
      native->u.syment.n_sclass = class;

      if (bfd_is_und_section (symbol->section))
	{
	  native->u.syment.n_scnum = N_UNDEF;
	  native->u.syment.n_value = symbol->value;
	}
      else if (bfd_is_com_section (symbol->section))
	{
	  native->u.syment.n_scnum = N_UNDEF;
	  native->u.syment.n_value = symbol->value;
	}
      else
	{
	  native->u.syment.n_scnum =
	    symbol->section->output_section->target_index;
	  native->u.syment.n_value = (symbol->value
				      + symbol->section->output_offset);
	  if (! obj_pe (abfd))
	    native->u.syment.n_value += symbol->section->output_section->vma;

	  /* Copy the any flags from the file header into the symbol.
	     FIXME: Why?  */
	  native->u.syment.n_flags = bfd_asymbol_bfd (& csym->symbol)->flags;
	}

      csym->native = native;
    }
  else
    csym->native->u.syment.n_sclass = class;

  return TRUE;
}