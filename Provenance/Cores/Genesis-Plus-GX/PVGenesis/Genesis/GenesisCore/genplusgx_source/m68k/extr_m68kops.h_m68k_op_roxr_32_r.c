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
typedef  int uint64 ;
typedef  int uint ;

/* Variables and functions */
 int CYC_SHIFT ; 
 int DX ; 
 int DY ; 
 int FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_X ; 
 int FLAG_Z ; 
 int MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int ROR_33 (int,int) ; 
 int ROR_33_64 (int,int) ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int XFLAG_AS_1 () ; 

__attribute__((used)) static void m68k_op_roxr_32_r(void)
{
#if M68K_USE_64_BIT

  uint*  r_dst = &DY;
  uint   orig_shift = DX & 0x3f;

  if(orig_shift != 0)
  {
    uint   shift = orig_shift % 33;
    uint64 src   = *r_dst;
    uint64 res   = src | (((uint64)XFLAG_AS_1()) << 32);

    res = ROR_33_64(res, shift);

    USE_CYCLES(orig_shift * CYC_SHIFT);

    FLAG_C = FLAG_X = res >> 24;
    res = MASK_OUT_ABOVE_32(res);

    *r_dst = res;
    FLAG_N = NFLAG_32(res);
    FLAG_Z = res;
    FLAG_V = VFLAG_CLEAR;
    return;
  }

  FLAG_C = FLAG_X;
  FLAG_N = NFLAG_32(*r_dst);
  FLAG_Z = *r_dst;
  FLAG_V = VFLAG_CLEAR;

#else

  uint* r_dst = &DY;
  uint orig_shift = DX & 0x3f;
  uint shift = orig_shift % 33;
  uint src = *r_dst;
  uint res = MASK_OUT_ABOVE_32((ROR_33(src, shift) & ~(1 << (32 - shift))) | (XFLAG_AS_1() << (32 - shift)));
  uint new_x_flag = src & (1 << (shift - 1));

  if(orig_shift != 0)
    USE_CYCLES(orig_shift * CYC_SHIFT);

  if(shift != 0)
  {
    *r_dst = res;
    FLAG_X = (new_x_flag != 0)<<8;
  }
  else
    res = src;
  FLAG_C = FLAG_X;
  FLAG_N = NFLAG_32(res);
  FLAG_Z = res;
  FLAG_V = VFLAG_CLEAR;

#endif
}