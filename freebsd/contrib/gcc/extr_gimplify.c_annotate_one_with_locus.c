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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ should_carry_locus_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
annotate_one_with_locus (tree t, location_t locus)
{
  if (EXPR_P (t) && ! EXPR_HAS_LOCATION (t) && should_carry_locus_p (t))
    SET_EXPR_LOCATION (t, locus);
}