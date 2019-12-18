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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  splay_tree ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wabi ; 
 scalar_t__ abi_version_at_least (int) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_empty_class (int /*<<< orphan*/ ) ; 
 scalar_t__ layout_conflict_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_binfo_offsets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_diffop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_zero_node ; 
 int /*<<< orphan*/  ssize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssizetype ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
layout_empty_base (tree binfo, tree eoc, splay_tree offsets)
{
  tree alignment;
  tree basetype = BINFO_TYPE (binfo);
  bool atend = false;

  /* This routine should only be used for empty classes.  */
  gcc_assert (is_empty_class (basetype));
  alignment = ssize_int (CLASSTYPE_ALIGN_UNIT (basetype));

  if (!integer_zerop (BINFO_OFFSET (binfo)))
    {
      if (abi_version_at_least (2))
	propagate_binfo_offsets
	  (binfo, size_diffop (size_zero_node, BINFO_OFFSET (binfo)));
      else
	warning (OPT_Wabi,
		 "offset of empty base %qT may not be ABI-compliant and may"
		 "change in a future version of GCC",
		 BINFO_TYPE (binfo));
    }

  /* This is an empty base class.  We first try to put it at offset
     zero.  */
  if (layout_conflict_p (binfo,
			 BINFO_OFFSET (binfo),
			 offsets,
			 /*vbases_p=*/0))
    {
      /* That didn't work.  Now, we move forward from the next
	 available spot in the class.  */
      atend = true;
      propagate_binfo_offsets (binfo, convert (ssizetype, eoc));
      while (1)
	{
	  if (!layout_conflict_p (binfo,
				  BINFO_OFFSET (binfo),
				  offsets,
				  /*vbases_p=*/0))
	    /* We finally found a spot where there's no overlap.  */
	    break;

	  /* There's overlap here, too.  Bump along to the next spot.  */
	  propagate_binfo_offsets (binfo, alignment);
	}
    }
  return atend;
}