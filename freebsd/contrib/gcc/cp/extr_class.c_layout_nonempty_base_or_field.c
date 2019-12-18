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
struct record_layout_info_s {int /*<<< orphan*/  bitpos; int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  splay_tree ;
typedef  struct record_layout_info_s* record_layout_info ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ BINFO_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ UNION_TYPE ; 
 int /*<<< orphan*/  abi_version_at_least (int) ; 
 int /*<<< orphan*/  bitsize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byte_position (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ layout_conflict_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  normalize_rli (struct record_layout_info_s*) ; 
 int /*<<< orphan*/  place_field (struct record_layout_info_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_binfo_offsets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_diffop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssizetype ; 

__attribute__((used)) static void
layout_nonempty_base_or_field (record_layout_info rli,
			       tree decl,
			       tree binfo,
			       splay_tree offsets)
{
  tree offset = NULL_TREE;
  bool field_p;
  tree type;

  if (binfo)
    {
      /* For the purposes of determining layout conflicts, we want to
	 use the class type of BINFO; TREE_TYPE (DECL) will be the
	 CLASSTYPE_AS_BASE version, which does not contain entries for
	 zero-sized bases.  */
      type = TREE_TYPE (binfo);
      field_p = false;
    }
  else
    {
      type = TREE_TYPE (decl);
      field_p = true;
    }

  /* Try to place the field.  It may take more than one try if we have
     a hard time placing the field without putting two objects of the
     same type at the same address.  */
  while (1)
    {
      struct record_layout_info_s old_rli = *rli;

      /* Place this field.  */
      place_field (rli, decl);
      offset = byte_position (decl);

      /* We have to check to see whether or not there is already
	 something of the same type at the offset we're about to use.
	 For example, consider:

	   struct S {};
	   struct T : public S { int i; };
	   struct U : public S, public T {};

	 Here, we put S at offset zero in U.  Then, we can't put T at
	 offset zero -- its S component would be at the same address
	 as the S we already allocated.  So, we have to skip ahead.
	 Since all data members, including those whose type is an
	 empty class, have nonzero size, any overlap can happen only
	 with a direct or indirect base-class -- it can't happen with
	 a data member.  */
      /* In a union, overlap is permitted; all members are placed at
	 offset zero.  */
      if (TREE_CODE (rli->t) == UNION_TYPE)
	break;
      /* G++ 3.2 did not check for overlaps when placing a non-empty
	 virtual base.  */
      if (!abi_version_at_least (2) && binfo && BINFO_VIRTUAL_P (binfo))
	break;
      if (layout_conflict_p (field_p ? type : binfo, offset,
			     offsets, field_p))
	{
	  /* Strip off the size allocated to this field.  That puts us
	     at the first place we could have put the field with
	     proper alignment.  */
	  *rli = old_rli;

	  /* Bump up by the alignment required for the type.  */
	  rli->bitpos
	    = size_binop (PLUS_EXPR, rli->bitpos,
			  bitsize_int (binfo
				       ? CLASSTYPE_ALIGN (type)
				       : TYPE_ALIGN (type)));
	  normalize_rli (rli);
	}
      else
	/* There was no conflict.  We're done laying out this field.  */
	break;
    }

  /* Now that we know where it will be placed, update its
     BINFO_OFFSET.  */
  if (binfo && CLASS_TYPE_P (BINFO_TYPE (binfo)))
    /* Indirect virtual bases may have a nonzero BINFO_OFFSET at
       this point because their BINFO_OFFSET is copied from another
       hierarchy.  Therefore, we may not need to add the entire
       OFFSET.  */
    propagate_binfo_offsets (binfo,
			     size_diffop (convert (ssizetype, offset),
					  convert (ssizetype,
						   BINFO_OFFSET (binfo))));
}