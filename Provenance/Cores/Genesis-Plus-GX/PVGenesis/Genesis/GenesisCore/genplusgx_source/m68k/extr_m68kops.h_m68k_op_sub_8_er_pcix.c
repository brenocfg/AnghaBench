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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_8 (int) ; 
 int DX ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_X ; 
 int FLAG_Z ; 
 void* MASK_OUT_ABOVE_8 (int) ; 
 int MASK_OUT_BELOW_8 (int) ; 
 int /*<<< orphan*/  NFLAG_8 (int) ; 
 int OPER_PCIX_8 () ; 
 int /*<<< orphan*/  VFLAG_SUB_8 (int,int,int) ; 

__attribute__((used)) static void m68k_op_sub_8_er_pcix(void)
{
  uint* r_dst = &DX;
  uint src = OPER_PCIX_8();
  uint dst = MASK_OUT_ABOVE_8(*r_dst);
  uint res = dst - src;

  FLAG_N = NFLAG_8(res);
  FLAG_X = FLAG_C = CFLAG_8(res);
  FLAG_V = VFLAG_SUB_8(src, dst, res);
  FLAG_Z = MASK_OUT_ABOVE_8(res);

  *r_dst = MASK_OUT_BELOW_8(*r_dst) | FLAG_Z;
}