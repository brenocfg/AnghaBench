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
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  ix86_expand_sse_cmp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ix86_expand_sse_fp_minmax (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_expand_sse_movcc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ix86_prepare_sse_fp_compare_args (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
ix86_expand_fp_vcond (rtx operands[])
{
  enum rtx_code code = GET_CODE (operands[3]);
  rtx cmp;

  code = ix86_prepare_sse_fp_compare_args (operands[0], code,
					   &operands[4], &operands[5]);
  if (code == UNKNOWN)
    return false;

  if (ix86_expand_sse_fp_minmax (operands[0], code, operands[4],
				 operands[5], operands[1], operands[2]))
    return true;

  cmp = ix86_expand_sse_cmp (operands[0], code, operands[4], operands[5],
			     operands[1], operands[2]);
  ix86_expand_sse_movcc (operands[0], cmp, operands[1], operands[2]);
  return true;
}