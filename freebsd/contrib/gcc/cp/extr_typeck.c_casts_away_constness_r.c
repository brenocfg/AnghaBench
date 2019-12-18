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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_qualified_type (int /*<<< orphan*/ ,int) ; 
 int cp_type_quals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
casts_away_constness_r (tree *t1, tree *t2)
{
  int quals1;
  int quals2;

  /* [expr.const.cast]

     For multi-level pointer to members and multi-level mixed pointers
     and pointers to members (conv.qual), the "member" aspect of a
     pointer to member level is ignored when determining if a const
     cv-qualifier has been cast away.  */
  /* [expr.const.cast]

     For  two  pointer types:

	    X1 is T1cv1,1 * ... cv1,N *   where T1 is not a pointer type
	    X2 is T2cv2,1 * ... cv2,M *   where T2 is not a pointer type
	    K is min(N,M)

     casting from X1 to X2 casts away constness if, for a non-pointer
     type T there does not exist an implicit conversion (clause
     _conv_) from:

	    Tcv1,(N-K+1) * cv1,(N-K+2) * ... cv1,N *

     to

	    Tcv2,(M-K+1) * cv2,(M-K+2) * ... cv2,M *.  */
  if ((!TYPE_PTR_P (*t1) && !TYPE_PTRMEM_P (*t1))
      || (!TYPE_PTR_P (*t2) && !TYPE_PTRMEM_P (*t2)))
    {
      *t1 = cp_build_qualified_type (void_type_node,
				     cp_type_quals (*t1));
      *t2 = cp_build_qualified_type (void_type_node,
				     cp_type_quals (*t2));
      return;
    }

  quals1 = cp_type_quals (*t1);
  quals2 = cp_type_quals (*t2);

  if (TYPE_PTRMEM_P (*t1))
    *t1 = TYPE_PTRMEM_POINTED_TO_TYPE (*t1);
  else
    *t1 = TREE_TYPE (*t1);
  if (TYPE_PTRMEM_P (*t2))
    *t2 = TYPE_PTRMEM_POINTED_TO_TYPE (*t2);
  else
    *t2 = TREE_TYPE (*t2);

  casts_away_constness_r (t1, t2);
  *t1 = build_pointer_type (*t1);
  *t2 = build_pointer_type (*t2);
  *t1 = cp_build_qualified_type (*t1, quals1);
  *t2 = cp_build_qualified_type (*t2, quals2);
}