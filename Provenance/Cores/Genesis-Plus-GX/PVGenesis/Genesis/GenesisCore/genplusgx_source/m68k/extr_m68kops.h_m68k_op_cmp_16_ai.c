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
typedef  void* uint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_16 (void*) ; 
 void* DX ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 void* FLAG_Z ; 
 void* MASK_OUT_ABOVE_16 (void*) ; 
 int /*<<< orphan*/  NFLAG_16 (void*) ; 
 void* OPER_AY_AI_16 () ; 
 int /*<<< orphan*/  VFLAG_SUB_16 (void*,void*,void*) ; 

__attribute__((used)) static void m68k_op_cmp_16_ai(void)
{
  uint src = OPER_AY_AI_16();
  uint dst = MASK_OUT_ABOVE_16(DX);
  uint res = dst - src;

  FLAG_N = NFLAG_16(res);
  FLAG_Z = MASK_OUT_ABOVE_16(res);
  FLAG_V = VFLAG_SUB_16(src, dst, res);
  FLAG_C = CFLAG_16(res);
}