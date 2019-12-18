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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARISON_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int reversed_comparison_code_parts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum rtx_code
reversed_comparison_code (rtx comparison, rtx insn)
{
  if (!COMPARISON_P (comparison))
    return UNKNOWN;
  return reversed_comparison_code_parts (GET_CODE (comparison),
					 XEXP (comparison, 0),
					 XEXP (comparison, 1), insn);
}