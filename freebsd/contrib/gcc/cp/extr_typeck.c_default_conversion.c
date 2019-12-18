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
 scalar_t__ INTEGRAL_OR_ENUMERATION_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decay_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_integral_promotions (int /*<<< orphan*/ ) ; 

tree
default_conversion (tree exp)
{
  /* Perform the integral promotions first so that bitfield
     expressions (which may promote to "int", even if the bitfield is
     declared "unsigned") are promoted correctly.  */
  if (INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (exp)))
    exp = perform_integral_promotions (exp);
  /* Perform the other conversions.  */
  exp = decay_conversion (exp);

  return exp;
}