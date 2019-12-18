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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  OPT_Wconversion ; 
 int /*<<< orphan*/  OPT_Woverflow ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_common_signed_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_fits_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_evaluation ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
unsigned_conversion_warning (tree result, tree operand)
{
  tree type = TREE_TYPE (result);

  if (TREE_CODE (operand) == INTEGER_CST
      && TREE_CODE (type) == INTEGER_TYPE
      && TYPE_UNSIGNED (type)
      && skip_evaluation == 0
      && !int_fits_type_p (operand, type))
    {
      if (!int_fits_type_p (operand, c_common_signed_type (type)))
	/* This detects cases like converting -129 or 256 to unsigned char.  */
	warning (OPT_Woverflow,
		 "large integer implicitly truncated to unsigned type");
      else
	warning (OPT_Wconversion,
		 "negative integer implicitly converted to unsigned type");
    }
}