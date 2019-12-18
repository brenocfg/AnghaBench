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
#define  INTEGER_CST 129 
 scalar_t__ NULL_TREE ; 
#define  REAL_CST 128 
 int TREE_CODE (scalar_t__) ; 

__attribute__((used)) static inline bool 
evolution_function_is_constant_p (tree chrec)
{
  if (chrec == NULL_TREE)
    return false;

  switch (TREE_CODE (chrec))
    {
    case INTEGER_CST:
    case REAL_CST:
      return true;
      
    default:
      return false;
    }
}