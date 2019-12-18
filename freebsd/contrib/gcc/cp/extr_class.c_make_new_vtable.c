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
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int build_primary_vtable (scalar_t__,scalar_t__) ; 
 int build_secondary_vtable (scalar_t__) ; 

__attribute__((used)) static int
make_new_vtable (tree t, tree binfo)
{
  if (binfo == TYPE_BINFO (t))
    /* In this case, it is *type*'s vtable we are modifying.  We start
       with the approximation that its vtable is that of the
       immediate base class.  */
    return build_primary_vtable (binfo, t);
  else
    /* This is our very own copy of `basetype' to play with.  Later,
       we will fill in all the virtual functions that override the
       virtual functions in these base classes which are not defined
       by the current type.  */
    return build_secondary_vtable (binfo);
}