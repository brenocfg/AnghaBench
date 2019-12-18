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
 int CFLAG_CLEAR ; 
 int CYC_SHIFT ; 
 int DX ; 
 int DY ; 
 int FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_X ; 
 int FLAG_Z ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int /*<<< orphan*/  NFLAG_CLEAR ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int XFLAG_CLEAR ; 
 int ZFLAG_SET ; 

__attribute__((used)) static void m68k_op_lsr_16_r(void)
{
  uint* r_dst = &DY;
  uint shift = DX & 0x3f;
  uint src = MASK_OUT_ABOVE_16(*r_dst);
  uint res = src >> shift;

  if(shift != 0)
  {
    USE_CYCLES(shift * CYC_SHIFT);

    if(shift <= 16)
    {
      *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
      FLAG_C = FLAG_X = (src >> (shift - 1))<<8;
      FLAG_N = NFLAG_CLEAR;
      FLAG_Z = res;
      FLAG_V = VFLAG_CLEAR;
      return;
    }

    *r_dst &= 0xffff0000;
    FLAG_X = XFLAG_CLEAR;
    FLAG_C = CFLAG_CLEAR;
    FLAG_N = NFLAG_CLEAR;
    FLAG_Z = ZFLAG_SET;
    FLAG_V = VFLAG_CLEAR;
    return;
  }

  FLAG_C = CFLAG_CLEAR;
  FLAG_N = NFLAG_16(src);
  FLAG_Z = src;
  FLAG_V = VFLAG_CLEAR;
}