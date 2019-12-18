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
 int CFLAG_CLEAR ; 
 int CYC_SHIFT ; 
 int DX ; 
 int DY ; 
 int FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int ROR_32 (int,int) ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 

__attribute__((used)) static void m68k_op_ror_32_r(void)
{
  uint* r_dst = &DY;
  uint orig_shift = DX & 0x3f;
  uint shift = orig_shift & 31;
  uint64 src = *r_dst;
  uint res = ROR_32(src, shift);

  if(orig_shift != 0)
  {
    USE_CYCLES(orig_shift * CYC_SHIFT);

    *r_dst = res;
    FLAG_C = (src >> ((shift - 1) & 31)) << 8;
    FLAG_N = NFLAG_32(res);
    FLAG_Z = res;
    FLAG_V = VFLAG_CLEAR;
    return;
  }

  FLAG_C = CFLAG_CLEAR;
  FLAG_N = NFLAG_32(src);
  FLAG_Z = src;
  FLAG_V = VFLAG_CLEAR;
}