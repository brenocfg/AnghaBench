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
typedef  scalar_t__ uint ;

/* Variables and functions */
 scalar_t__ AX ; 
 int /*<<< orphan*/  CFLAG_SUB_32 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 scalar_t__ MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_32 (scalar_t__) ; 
 int /*<<< orphan*/  NFLAG_32 (scalar_t__) ; 
 int /*<<< orphan*/  OPER_AL_16 () ; 
 int /*<<< orphan*/  VFLAG_SUB_32 (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void m68k_op_cmpa_16_al(void)
{
  uint src = MAKE_INT_16(OPER_AL_16());
  uint dst = AX;
  uint res = dst - src;

  FLAG_N = NFLAG_32(res);
  FLAG_Z = MASK_OUT_ABOVE_32(res);
  FLAG_V = VFLAG_SUB_32(src, dst, res);
  FLAG_C = CFLAG_SUB_32(src, dst, res);
}