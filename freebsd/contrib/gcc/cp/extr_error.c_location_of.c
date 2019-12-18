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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (scalar_t__) ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_FUNCTION (scalar_t__) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_DECL (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 

__attribute__((used)) static location_t
location_of (tree t)
{
  if (TREE_CODE (t) == PARM_DECL && DECL_CONTEXT (t))
    t = DECL_CONTEXT (t);
  else if (TYPE_P (t))
    t = TYPE_MAIN_DECL (t);
  else if (TREE_CODE (t) == OVERLOAD)
    t = OVL_FUNCTION (t);

  return DECL_SOURCE_LOCATION (t);
}