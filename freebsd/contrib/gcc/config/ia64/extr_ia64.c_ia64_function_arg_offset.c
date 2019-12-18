#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {int words; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TYPE_ALIGN (scalar_t__) ; 

__attribute__((used)) static int
ia64_function_arg_offset (CUMULATIVE_ARGS *cum, tree type, int words)
{
  if ((cum->words & 1) == 0)
    return 0;

  if (type
      && TREE_CODE (type) != INTEGER_TYPE
      && TREE_CODE (type) != REAL_TYPE)
    return TYPE_ALIGN (type) > 8 * BITS_PER_UNIT;
  else
    return words > 1;
}