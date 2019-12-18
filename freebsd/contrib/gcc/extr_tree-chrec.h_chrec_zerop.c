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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int integer_zerop (scalar_t__) ; 

__attribute__((used)) static inline bool 
chrec_zerop (tree chrec)
{
  if (chrec == NULL_TREE)
    return false;
  
  if (TREE_CODE (chrec) == INTEGER_CST)
    return integer_zerop (chrec);
  
  return false;
}