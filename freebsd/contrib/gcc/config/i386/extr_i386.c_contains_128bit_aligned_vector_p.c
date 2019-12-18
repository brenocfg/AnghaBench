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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
#define  ARRAY_TYPE 131 
 int /*<<< orphan*/  BINFO_BASE_ITERATE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int FIELD_DECL ; 
#define  QUAL_UNION_TYPE 130 
#define  RECORD_TYPE 129 
 scalar_t__ SSE_REG_MODE_P (int) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_USER_ALIGN (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static bool
contains_128bit_aligned_vector_p (tree type)
{
  enum machine_mode mode = TYPE_MODE (type);
  if (SSE_REG_MODE_P (mode)
      && (!TYPE_USER_ALIGN (type) || TYPE_ALIGN (type) > 128))
    return true;
  if (TYPE_ALIGN (type) < 128)
    return false;

  if (AGGREGATE_TYPE_P (type))
    {
      /* Walk the aggregates recursively.  */
      switch (TREE_CODE (type))
	{
	case RECORD_TYPE:
	case UNION_TYPE:
	case QUAL_UNION_TYPE:
	  {
	    tree field;

	    if (TYPE_BINFO (type))
	      {
		tree binfo, base_binfo;
		int i;

		for (binfo = TYPE_BINFO (type), i = 0;
		     BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
		  if (contains_128bit_aligned_vector_p
		      (BINFO_TYPE (base_binfo)))
		    return true;
	      }
	    /* And now merge the fields of structure.  */
	    for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	      {
		if (TREE_CODE (field) == FIELD_DECL
		    && contains_128bit_aligned_vector_p (TREE_TYPE (field)))
		  return true;
	      }
	    break;
	  }

	case ARRAY_TYPE:
	  /* Just for use if some languages passes arrays by value.  */
	  if (contains_128bit_aligned_vector_p (TREE_TYPE (type)))
	    return true;
	  break;

	default:
	  gcc_unreachable ();
	}
    }
  return false;
}