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
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DERIVED_FROM_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
reference_related_p (tree t1, tree t2)
{
  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  /* [dcl.init.ref]

     Given types "cv1 T1" and "cv2 T2," "cv1 T1" is reference-related
     to "cv2 T2" if T1 is the same type as T2, or T1 is a base class
     of T2.  */
  return (same_type_p (t1, t2)
	  || (CLASS_TYPE_P (t1) && CLASS_TYPE_P (t2)
	      && DERIVED_FROM_P (t1, t2)));
}