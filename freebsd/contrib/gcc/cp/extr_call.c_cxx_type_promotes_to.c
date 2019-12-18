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
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_decays_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_promotes_to (int /*<<< orphan*/ ) ; 

tree
cxx_type_promotes_to (tree type)
{
  tree promote;

  /* Perform the array-to-pointer and function-to-pointer
     conversions.  */
  type = type_decays_to (type);

  promote = type_promotes_to (type);
  if (same_type_p (type, promote))
    promote = type;

  return promote;
}