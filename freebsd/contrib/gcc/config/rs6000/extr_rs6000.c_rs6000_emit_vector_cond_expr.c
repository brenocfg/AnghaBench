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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_ALTIVEC ; 
 int /*<<< orphan*/  rs6000_emit_vector_compare (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rs6000_emit_vector_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
rs6000_emit_vector_cond_expr (rtx dest, rtx op1, rtx op2,
			      rtx cond, rtx cc_op0, rtx cc_op1)
{
  enum machine_mode dest_mode = GET_MODE (dest);
  enum rtx_code rcode = GET_CODE (cond);
  rtx mask;

  if (!TARGET_ALTIVEC)
    return 0;

  /* Get the vector mask for the given relational operations.  */
  mask = rs6000_emit_vector_compare (rcode, cc_op0, cc_op1, dest_mode);

  rs6000_emit_vector_select (dest, op1, op2, mask);

  return 1;
}