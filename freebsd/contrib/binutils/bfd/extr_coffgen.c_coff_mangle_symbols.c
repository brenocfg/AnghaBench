#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_11__* p; int /*<<< orphan*/  l; } ;
struct TYPE_29__ {TYPE_12__ x_scnlen; } ;
struct TYPE_42__ {TYPE_6__* p; int /*<<< orphan*/  l; } ;
struct TYPE_43__ {TYPE_7__ x_endndx; } ;
struct TYPE_44__ {TYPE_8__ x_fcn; } ;
struct TYPE_40__ {TYPE_4__* p; int /*<<< orphan*/  l; } ;
struct TYPE_26__ {TYPE_9__ x_fcnary; TYPE_5__ x_tagndx; } ;
struct TYPE_30__ {TYPE_13__ x_csect; TYPE_10__ x_sym; } ;
struct TYPE_38__ {int n_value; int n_numaux; } ;
struct TYPE_31__ {TYPE_14__ auxent; TYPE_3__ syment; } ;
struct TYPE_32__ {scalar_t__ fix_scnlen; TYPE_15__ u; scalar_t__ fix_end; scalar_t__ fix_tag; scalar_t__ fix_line; scalar_t__ fix_value; scalar_t__ offset; } ;
typedef  TYPE_16__ combined_entry_type ;
struct TYPE_37__ {int flags; TYPE_21__* section; } ;
struct TYPE_33__ {TYPE_2__ symbol; TYPE_16__* native; } ;
typedef  TYPE_17__ coff_symbol_type ;
typedef  int bfd_vma ;
struct TYPE_34__ {int /*<<< orphan*/ ** outsymbols; } ;
typedef  TYPE_18__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_41__ {int /*<<< orphan*/  offset; } ;
struct TYPE_39__ {int /*<<< orphan*/  offset; } ;
struct TYPE_36__ {TYPE_1__* output_section; } ;
struct TYPE_35__ {int line_filepos; } ;
struct TYPE_27__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_DEBUGGING ; 
 int /*<<< orphan*/  N_DEBUG ; 
 int bfd_coff_linesz (TYPE_18__*) ; 
 unsigned int bfd_get_symcount (TYPE_18__*) ; 
 TYPE_21__* coff_section_from_bfd_index (TYPE_18__*,int /*<<< orphan*/ ) ; 
 TYPE_17__* coff_symbol_from (TYPE_18__*,int /*<<< orphan*/ *) ; 

void
coff_mangle_symbols (bfd *bfd_ptr)
{
  unsigned int symbol_count = bfd_get_symcount (bfd_ptr);
  asymbol **symbol_ptr_ptr = bfd_ptr->outsymbols;
  unsigned int symbol_index;

  for (symbol_index = 0; symbol_index < symbol_count; symbol_index++)
    {
      coff_symbol_type *coff_symbol_ptr =
      coff_symbol_from (bfd_ptr, symbol_ptr_ptr[symbol_index]);

      if (coff_symbol_ptr && coff_symbol_ptr->native)
	{
	  int i;
	  combined_entry_type *s = coff_symbol_ptr->native;

	  if (s->fix_value)
	    {
	      /* FIXME: We should use a union here.  */
	      s->u.syment.n_value =
		(bfd_vma)((combined_entry_type *)
			  ((unsigned long) s->u.syment.n_value))->offset;
	      s->fix_value = 0;
	    }
	  if (s->fix_line)
	    {
	      /* The value is the offset into the line number entries
                 for the symbol's section.  On output, the symbol's
                 section should be N_DEBUG.  */
	      s->u.syment.n_value =
		(coff_symbol_ptr->symbol.section->output_section->line_filepos
		 + s->u.syment.n_value * bfd_coff_linesz (bfd_ptr));
	      coff_symbol_ptr->symbol.section =
		coff_section_from_bfd_index (bfd_ptr, N_DEBUG);
	      BFD_ASSERT (coff_symbol_ptr->symbol.flags & BSF_DEBUGGING);
	    }
	  for (i = 0; i < s->u.syment.n_numaux; i++)
	    {
	      combined_entry_type *a = s + i + 1;
	      if (a->fix_tag)
		{
		  a->u.auxent.x_sym.x_tagndx.l =
		    a->u.auxent.x_sym.x_tagndx.p->offset;
		  a->fix_tag = 0;
		}
	      if (a->fix_end)
		{
		  a->u.auxent.x_sym.x_fcnary.x_fcn.x_endndx.l =
		    a->u.auxent.x_sym.x_fcnary.x_fcn.x_endndx.p->offset;
		  a->fix_end = 0;
		}
	      if (a->fix_scnlen)
		{
		  a->u.auxent.x_csect.x_scnlen.l =
		    a->u.auxent.x_csect.x_scnlen.p->offset;
		  a->fix_scnlen = 0;
		}
	    }
	}
    }
}