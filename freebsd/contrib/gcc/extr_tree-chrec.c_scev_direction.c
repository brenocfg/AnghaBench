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
typedef  enum ev_direction { ____Placeholder_ev_direction } ev_direction ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int EV_DIR_DECREASES ; 
 int EV_DIR_GROWS ; 
 int EV_DIR_UNKNOWN ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evolution_function_is_affine_p (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_sign_bit (int /*<<< orphan*/ ) ; 

enum ev_direction
scev_direction (tree chrec)
{
  tree step;

  if (!evolution_function_is_affine_p (chrec))
    return EV_DIR_UNKNOWN;

  step = CHREC_RIGHT (chrec);
  if (TREE_CODE (step) != INTEGER_CST)
    return EV_DIR_UNKNOWN;

  if (tree_int_cst_sign_bit (step))
    return EV_DIR_DECREASES;
  else
    return EV_DIR_GROWS;
}