#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mep_hi_fixup {TYPE_2__* fixp; int /*<<< orphan*/  seg; struct mep_hi_fixup* next; } ;
struct TYPE_5__ {TYPE_2__* fix_root; } ;
typedef  TYPE_1__ segment_info_type ;
struct TYPE_6__ {scalar_t__ fx_addsy; scalar_t__ fx_offset; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; struct TYPE_6__* fx_next; } ;
typedef  TYPE_2__ fixS ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_HI16 ; 
 scalar_t__ BFD_RELOC_LO16 ; 
 scalar_t__ FX_OPINFO_R_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mep_hi_fixup* mep_hi_fixup_list ; 
 TYPE_1__* seg_info (int /*<<< orphan*/ ) ; 

void
mep_frob_file ()
{
  struct mep_hi_fixup * l;

  for (l = mep_hi_fixup_list; l != NULL; l = l->next)
    {
      segment_info_type * seginfo;
      int pass;

      assert (FX_OPINFO_R_TYPE (l->fixp) == BFD_RELOC_HI16
	      || FX_OPINFO_R_TYPE (l->fixp) == BFD_RELOC_LO16);

      /* Check quickly whether the next fixup happens to be a matching low.  */
      if (l->fixp->fx_next != NULL
	  && FX_OPINFO_R_TYPE (l->fixp->fx_next) == BFD_RELOC_LO16
	  && l->fixp->fx_addsy == l->fixp->fx_next->fx_addsy
	  && l->fixp->fx_offset == l->fixp->fx_next->fx_offset)
	continue;

      /* Look through the fixups for this segment for a matching
         `low'.  When we find one, move the high just in front of it.
         We do this in two passes.  In the first pass, we try to find
         a unique `low'.  In the second pass, we permit multiple
         high's relocs for a single `low'.  */
      seginfo = seg_info (l->seg);
      for (pass = 0; pass < 2; pass++)
	{
	  fixS * f;
	  fixS * prev;

	  prev = NULL;
	  for (f = seginfo->fix_root; f != NULL; f = f->fx_next)
	    {
	      /* Check whether this is a `low' fixup which matches l->fixp.  */
	      if (FX_OPINFO_R_TYPE (f) == BFD_RELOC_LO16
		  && f->fx_addsy == l->fixp->fx_addsy
		  && f->fx_offset == l->fixp->fx_offset
		  && (pass == 1
		      || prev == NULL
		      || (FX_OPINFO_R_TYPE (prev) != BFD_RELOC_HI16)
		      || prev->fx_addsy != f->fx_addsy
		      || prev->fx_offset !=  f->fx_offset))
		{
		  fixS ** pf;

		  /* Move l->fixp before f.  */
		  for (pf = &seginfo->fix_root;
		       * pf != l->fixp;
		       pf = & (* pf)->fx_next)
		    assert (* pf != NULL);

		  * pf = l->fixp->fx_next;

		  l->fixp->fx_next = f;
		  if (prev == NULL)
		    seginfo->fix_root = l->fixp;
		  else
		    prev->fx_next = l->fixp;

		  break;
		}

	      prev = f;
	    }

	  if (f != NULL)
	    break;

	  if (pass == 1)
	    as_warn_where (l->fixp->fx_file, l->fixp->fx_line,
			   _("Unmatched high relocation"));
	}
    }
}