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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_PACKED (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TARGET_FPU ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 

__attribute__((used)) static void
scan_record_type (tree type, int *intregs_p, int *fpregs_p, int *packed_p)
{
  tree field;

  for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
    {
      if (TREE_CODE (field) == FIELD_DECL)
	{
	  if (TREE_CODE (TREE_TYPE (field)) == RECORD_TYPE)
	    scan_record_type (TREE_TYPE (field), intregs_p, fpregs_p, 0);
	  else if ((FLOAT_TYPE_P (TREE_TYPE (field))
		   || TREE_CODE (TREE_TYPE (field)) == VECTOR_TYPE)
		  && TARGET_FPU)
	    *fpregs_p = 1;
	  else
	    *intregs_p = 1;

	  if (packed_p && DECL_PACKED (field))
	    *packed_p = 1;
	}
    }
}