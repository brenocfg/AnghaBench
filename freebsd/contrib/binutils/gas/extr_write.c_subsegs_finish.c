#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct frchain {int /*<<< orphan*/  frch_subseg; struct frchain* frch_next; } ;
struct TYPE_13__ {struct frchain* frchainP; } ;
typedef  TYPE_1__ segment_info_type ;
struct TYPE_14__ {struct TYPE_14__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_17__ {int /*<<< orphan*/ * fr_next; scalar_t__ fr_fix; } ;
struct TYPE_16__ {TYPE_2__* sections; } ;
struct TYPE_15__ {unsigned int entsize; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int SEC_MERGE ; 
 int SUB_SEGMENT_ALIGN (TYPE_3__*,struct frchain*) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_align_code (int,int /*<<< orphan*/ ) ; 
 TYPE_9__* frag_now ; 
 int /*<<< orphan*/  frag_wane (TYPE_9__*) ; 
 int /*<<< orphan*/  had_errors () ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 
 TYPE_3__* now_seg ; 
 TYPE_1__* seg_info (TYPE_2__*) ; 
 TYPE_5__* stdoutput ; 
 int /*<<< orphan*/  subseg_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ subseg_text_p (TYPE_3__*) ; 

void
subsegs_finish (void)
{
  struct frchain *frchainP;
  asection *s;

  for (s = stdoutput->sections; s; s = s->next)
    {
      segment_info_type *seginfo = seg_info (s);
      if (!seginfo)
	continue;

      for (frchainP = seginfo->frchainP;
	   frchainP != NULL;
	   frchainP = frchainP->frch_next)
	{
	  int alignment = 0;

	  subseg_set (s, frchainP->frch_subseg);

	  /* This now gets called even if we had errors.  In that case,
	     any alignment is meaningless, and, moreover, will look weird
	     if we are generating a listing.  */
	  if (!had_errors ())
	    {
	      alignment = SUB_SEGMENT_ALIGN (now_seg, frchainP);
	      if ((bfd_get_section_flags (now_seg->owner, now_seg) & SEC_MERGE)
		  && now_seg->entsize)
		{
		  unsigned int entsize = now_seg->entsize;
		  int entalign = 0;

		  while ((entsize & 1) == 0)
		    {
		      ++entalign;
		      entsize >>= 1;
		    }
		  if (entalign > alignment)
		    alignment = entalign;
		}
	    }

	  if (subseg_text_p (now_seg))
	    frag_align_code (alignment, 0);
	  else
	    frag_align (alignment, 0, 0);

	  /* frag_align will have left a new frag.
	     Use this last frag for an empty ".fill".

	     For this segment ...
	     Create a last frag. Do not leave a "being filled in frag".  */
	  frag_wane (frag_now);
	  frag_now->fr_fix = 0;
	  know (frag_now->fr_next == NULL);
	}
    }
}