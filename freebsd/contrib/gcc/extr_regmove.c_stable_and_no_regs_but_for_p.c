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
typedef  int /*<<< orphan*/  RTX_CODE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_RTX_CLASS (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_RTX_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM ; 
 int /*<<< orphan*/  REG ; 
#define  RTX_BIN_ARITH 135 
#define  RTX_BITFIELD_OPS 134 
#define  RTX_COMM_ARITH 133 
#define  RTX_COMM_COMPARE 132 
#define  RTX_COMPARE 131 
#define  RTX_OBJ 130 
#define  RTX_TERNARY 129 
#define  RTX_UNARY 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtx_unstable_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stable_and_no_regs_but_for_p (rtx x, rtx src, rtx dst)
{
  RTX_CODE code = GET_CODE (x);
  switch (GET_RTX_CLASS (code))
    {
    case RTX_UNARY:
    case RTX_BIN_ARITH:
    case RTX_COMM_ARITH:
    case RTX_COMPARE:
    case RTX_COMM_COMPARE:
    case RTX_TERNARY:
    case RTX_BITFIELD_OPS:
      {
	int i;
	const char *fmt = GET_RTX_FORMAT (code);
	for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
	  if (fmt[i] == 'e'
	      && ! stable_and_no_regs_but_for_p (XEXP (x, i), src, dst))
	      return 0;
	return 1;
      }
    case RTX_OBJ:
      if (code == REG)
	return x == src || x == dst;
      /* If this is a MEM, look inside - there might be a register hidden in
	 the address of an unchanging MEM.  */
      if (code == MEM
	  && ! stable_and_no_regs_but_for_p (XEXP (x, 0), src, dst))
	return 0;
      /* Fall through.  */
    default:
      return ! rtx_unstable_p (x);
    }
}