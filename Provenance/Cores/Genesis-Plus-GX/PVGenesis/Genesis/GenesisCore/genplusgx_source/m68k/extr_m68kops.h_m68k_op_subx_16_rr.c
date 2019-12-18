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
 int /*<<< orphan*/  CFLAG_16 (int) ; 
 int DX ; 
 int DY ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_X ; 
 int FLAG_Z ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int /*<<< orphan*/  VFLAG_SUB_16 (int,int,int) ; 
 int XFLAG_AS_1 () ; 

__attribute__((used)) static void m68k_op_subx_16_rr(void)
{
  uint* r_dst = &DX;
  uint src = MASK_OUT_ABOVE_16(DY);
  uint dst = MASK_OUT_ABOVE_16(*r_dst);
  uint res = dst - src - XFLAG_AS_1();

  FLAG_N = NFLAG_16(res);
  FLAG_X = FLAG_C = CFLAG_16(res);
  FLAG_V = VFLAG_SUB_16(src, dst, res);

  res = MASK_OUT_ABOVE_16(res);
  FLAG_Z |= res;

  *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
}