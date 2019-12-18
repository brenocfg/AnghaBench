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
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  DX ; 
 int /*<<< orphan*/  EXCEPTION_CHK ; 
 int /*<<< orphan*/  FLAG_C ; 
 int FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 scalar_t__ MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPER_AY_DI_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  ZFLAG_16 (scalar_t__) ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_chk_16_di(void)
{
  sint src = MAKE_INT_16(DX);
  sint bound = MAKE_INT_16(OPER_AY_DI_16());

  FLAG_Z = ZFLAG_16(src); /* Undocumented */
  FLAG_V = VFLAG_CLEAR;   /* Undocumented */
  FLAG_C = CFLAG_CLEAR;   /* Undocumented */

  if(src >= 0 && src <= bound)
  {
    return;
  }
  FLAG_N = (src < 0)<<7;
  m68ki_exception_trap(EXCEPTION_CHK);
}