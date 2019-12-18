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
 int CLASSTYPE_EMPTY_P (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  IS_AGGR_TYPE (scalar_t__) ; 
 scalar_t__ abi_version_at_least (int) ; 
 scalar_t__ error_mark_node ; 
 int integer_zerop (int /*<<< orphan*/ ) ; 

int
is_empty_class (tree type)
{
  if (type == error_mark_node)
    return 0;

  if (! IS_AGGR_TYPE (type))
    return 0;

  /* In G++ 3.2, whether or not a class was empty was determined by
     looking at its size.  */
  if (abi_version_at_least (2))
    return CLASSTYPE_EMPTY_P (type);
  else
    return integer_zerop (CLASSTYPE_SIZE (type));
}