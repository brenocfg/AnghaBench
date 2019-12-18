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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_NOT_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 int TRUTH_OR_EXPR ; 
 int TRUTH_XOR_EXPR ; 
 scalar_t__ tcc_comparison ; 

__attribute__((used)) static int
truth_value_p (enum tree_code code)
{
  return (TREE_CODE_CLASS (code) == tcc_comparison
	  || code == TRUTH_AND_EXPR || code == TRUTH_ANDIF_EXPR
	  || code == TRUTH_OR_EXPR || code == TRUTH_ORIF_EXPR
	  || code == TRUTH_XOR_EXPR || code == TRUTH_NOT_EXPR);
}