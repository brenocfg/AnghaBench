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
typedef  int hashval_t ;

/* Variables and functions */
#define  ENUMERAL_TYPE 132 
#define  POINTER_TYPE 131 
#define  QUAL_UNION_TYPE 130 
#define  RECORD_TYPE 129 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 void* TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
 scalar_t__ TYPE_VALUES (scalar_t__) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static hashval_t
c_type_hash (const void *p)
{
  int i = 0;
  int shift, size;
  tree t = (tree) p;
  tree t2;
  switch (TREE_CODE (t))
    {
    /* For pointers, hash on pointee type plus some swizzling.  */
    case POINTER_TYPE:
      return c_type_hash (TREE_TYPE (t)) ^ 0x3003003;
    /* Hash on number of elements and total size.  */
    case ENUMERAL_TYPE:
      shift = 3;
      t2 = TYPE_VALUES (t);
      break;
    case RECORD_TYPE:
      shift = 0;
      t2 = TYPE_FIELDS (t);
      break;
    case QUAL_UNION_TYPE:
      shift = 1;
      t2 = TYPE_FIELDS (t);
      break;
    case UNION_TYPE:
      shift = 2;
      t2 = TYPE_FIELDS (t);
      break;
    default:
      gcc_unreachable ();
    }
  for (; t2; t2 = TREE_CHAIN (t2))
    i++;
  size = TREE_INT_CST_LOW (TYPE_SIZE (t));
  return ((size << 24) | (i << shift));
}