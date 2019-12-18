#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {unsigned int x_lnnoptr; } ;
struct TYPE_21__ {TYPE_3__ x_fcn; } ;
struct TYPE_22__ {TYPE_4__ x_fcnary; } ;
union internal_auxent {TYPE_5__ x_sym; } ;
struct TYPE_18__ {scalar_t__ n_numaux; } ;
struct TYPE_19__ {union internal_auxent auxent; TYPE_1__ syment; } ;
struct TYPE_25__ {TYPE_2__ u; } ;
typedef  TYPE_8__ combined_entry_type ;
struct TYPE_16__ {TYPE_7__* section; } ;
struct TYPE_26__ {TYPE_11__ symbol; int /*<<< orphan*/  done_lineno; TYPE_10__* lineno; TYPE_8__* native; } ;
typedef  TYPE_9__ coff_symbol_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_23__ {int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {scalar_t__ line_number; TYPE_6__ u; } ;
typedef  TYPE_10__ alent ;
struct TYPE_24__ {TYPE_14__* output_section; scalar_t__ output_offset; int /*<<< orphan*/ * owner; } ;
struct TYPE_17__ {unsigned int moving_line_filepos; scalar_t__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 unsigned int bfd_coff_linesz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_is_const_section (TYPE_14__*) ; 
 int /*<<< orphan*/  coff_write_symbol (int /*<<< orphan*/ *,TYPE_11__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
coff_write_native_symbol (bfd *abfd,
			  coff_symbol_type *symbol,
			  bfd_vma *written,
			  bfd_size_type *string_size_p,
			  asection **debug_string_section_p,
			  bfd_size_type *debug_string_size_p)
{
  combined_entry_type *native = symbol->native;
  alent *lineno = symbol->lineno;

  /* If this symbol has an associated line number, we must store the
     symbol index in the line number field.  We also tag the auxent to
     point to the right place in the lineno table.  */
  if (lineno && !symbol->done_lineno && symbol->symbol.section->owner != NULL)
    {
      unsigned int count = 0;

      lineno[count].u.offset = *written;
      if (native->u.syment.n_numaux)
	{
	  union internal_auxent *a = &((native + 1)->u.auxent);

	  a->x_sym.x_fcnary.x_fcn.x_lnnoptr =
	    symbol->symbol.section->output_section->moving_line_filepos;
	}

      /* Count and relocate all other linenumbers.  */
      count++;
      while (lineno[count].line_number != 0)
	{
	  lineno[count].u.offset +=
	    (symbol->symbol.section->output_section->vma
	     + symbol->symbol.section->output_offset);
	  count++;
	}
      symbol->done_lineno = TRUE;

      if (! bfd_is_const_section (symbol->symbol.section->output_section))
	symbol->symbol.section->output_section->moving_line_filepos +=
	  count * bfd_coff_linesz (abfd);
    }

  return coff_write_symbol (abfd, &(symbol->symbol), native, written,
			    string_size_p, debug_string_section_p,
			    debug_string_size_p);
}