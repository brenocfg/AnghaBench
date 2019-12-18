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
struct mips_hi_fixup {TYPE_2__* fixp; int /*<<< orphan*/  seg; struct mips_hi_fixup* next; } ;
struct TYPE_5__ {TYPE_2__* fix_root; } ;
typedef  TYPE_1__ segment_info_type ;
struct TYPE_6__ {scalar_t__ fx_r_type; scalar_t__ fx_addsy; scalar_t__ fx_offset; struct TYPE_6__* fx_next; } ;
typedef  TYPE_2__ fixS ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_LO16 ; 
 scalar_t__ BFD_RELOC_MIPS16_LO16 ; 
 scalar_t__ BFD_RELOC_MIPS_GOT16 ; 
 int FALSE ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ fixup_has_matching_lo_p (TYPE_2__*) ; 
 struct mips_hi_fixup* mips_hi_fixup_list ; 
 int /*<<< orphan*/  pic_need_relax (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ reloc_needs_lo_p (scalar_t__) ; 
 TYPE_1__* seg_info (int /*<<< orphan*/ ) ; 

void
mips_frob_file (void)
{
  struct mips_hi_fixup *l;

  for (l = mips_hi_fixup_list; l != NULL; l = l->next)
    {
      segment_info_type *seginfo;
      bfd_boolean matched_lo_p;
      fixS **hi_pos, **lo_pos, **pos;

      assert (reloc_needs_lo_p (l->fixp->fx_r_type));

      /* If a GOT16 relocation turns out to be against a global symbol,
	 there isn't supposed to be a matching LO.  */
      if (l->fixp->fx_r_type == BFD_RELOC_MIPS_GOT16
	  && !pic_need_relax (l->fixp->fx_addsy, l->seg))
	continue;

      /* Check quickly whether the next fixup happens to be a matching %lo.  */
      if (fixup_has_matching_lo_p (l->fixp))
	continue;

      seginfo = seg_info (l->seg);

      /* Set HI_POS to the position of this relocation in the chain.
	 Set LO_POS to the position of the chosen low-part relocation.
	 MATCHED_LO_P is true on entry to the loop if *POS is a low-part
	 relocation that matches an immediately-preceding high-part
	 relocation.  */
      hi_pos = NULL;
      lo_pos = NULL;
      matched_lo_p = FALSE;
      for (pos = &seginfo->fix_root; *pos != NULL; pos = &(*pos)->fx_next)
	{
	  if (*pos == l->fixp)
	    hi_pos = pos;

	  if (((*pos)->fx_r_type == BFD_RELOC_LO16
	       || (*pos)->fx_r_type == BFD_RELOC_MIPS16_LO16)
	      && (*pos)->fx_addsy == l->fixp->fx_addsy
	      && (*pos)->fx_offset >= l->fixp->fx_offset
	      && (lo_pos == NULL
		  || (*pos)->fx_offset < (*lo_pos)->fx_offset
		  || (!matched_lo_p
		      && (*pos)->fx_offset == (*lo_pos)->fx_offset)))
	    lo_pos = pos;

	  matched_lo_p = (reloc_needs_lo_p ((*pos)->fx_r_type)
			  && fixup_has_matching_lo_p (*pos));
	}

      /* If we found a match, remove the high-part relocation from its
	 current position and insert it before the low-part relocation.
	 Make the offsets match so that fixup_has_matching_lo_p()
	 will return true.

	 We don't warn about unmatched high-part relocations since some
	 versions of gcc have been known to emit dead "lui ...%hi(...)"
	 instructions.  */
      if (lo_pos != NULL)
	{
	  l->fixp->fx_offset = (*lo_pos)->fx_offset;
	  if (l->fixp->fx_next != *lo_pos)
	    {
	      *hi_pos = l->fixp->fx_next;
	      l->fixp->fx_next = *lo_pos;
	      *lo_pos = l->fixp;
	    }
	}
    }
}