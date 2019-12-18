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
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_automatically_generated_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 

tree 
chrec_fold_minus (tree type, 
		  tree op0, 
		  tree op1)
{
  if (automatically_generated_chrec_p (op0)
      || automatically_generated_chrec_p (op1))
    return chrec_fold_automatically_generated_operands (op0, op1);

  if (integer_zerop (op1))
    return op0;
  
  return chrec_fold_plus_1 (MINUS_EXPR, type, op0, op1);
}