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
 int /*<<< orphan*/  BASELINK_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  error_operand_p (scalar_t__) ; 
 scalar_t__ lookup_member (scalar_t__,scalar_t__,int,int) ; 

tree
lookup_fnfields (tree xbasetype, tree name, int protect)
{
  tree rval = lookup_member (xbasetype, name, protect, /*want_type=*/false);

  /* Ignore non-functions, but propagate the ambiguity list.  */
  if (!error_operand_p (rval)
      && (rval && !BASELINK_P (rval)))
    return NULL_TREE;

  return rval;
}