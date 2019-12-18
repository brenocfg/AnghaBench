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

/* Variables and functions */
 int ARRAY_TYPE ; 
#define  BOOLEAN_TYPE 137 
#define  COMPLEX_TYPE 136 
#define  ENUMERAL_TYPE 135 
#define  INTEGER_TYPE 134 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
#define  QUAL_UNION_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 

__attribute__((used)) static bool
type_to_consider (tree type)
{
  /* Strip the *'s off.  */
  type = TYPE_MAIN_VARIANT (type);
  while (POINTER_TYPE_P (type) || TREE_CODE (type) == ARRAY_TYPE)
    type = TYPE_MAIN_VARIANT (TREE_TYPE (type));

  switch (TREE_CODE (type))
    {
    case BOOLEAN_TYPE:
    case COMPLEX_TYPE:
    case ENUMERAL_TYPE:
    case INTEGER_TYPE:
    case QUAL_UNION_TYPE:
    case REAL_TYPE:
    case RECORD_TYPE:
    case UNION_TYPE:
    case VECTOR_TYPE:
    case VOID_TYPE:
      return true;
  
    default:
      return false;
    }
}