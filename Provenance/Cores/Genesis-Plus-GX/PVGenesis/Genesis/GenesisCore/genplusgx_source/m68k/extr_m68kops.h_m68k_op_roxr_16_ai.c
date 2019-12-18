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
 int EA_AY_AI_16 () ; 
 int FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_X ; 
 int FLAG_Z ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int ROR_17 (int,int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int XFLAG_AS_1 () ; 
 int m68ki_read_16 (int) ; 
 int /*<<< orphan*/  m68ki_write_16 (int,int) ; 

__attribute__((used)) static void m68k_op_roxr_16_ai(void)
{
  uint ea = EA_AY_AI_16();
  uint src = m68ki_read_16(ea);
  uint res = ROR_17(src | (XFLAG_AS_1() << 16), 1);

  FLAG_C = FLAG_X = res >> 8;
  res = MASK_OUT_ABOVE_16(res);

  m68ki_write_16(ea, res);

  FLAG_N = NFLAG_16(res);
  FLAG_Z = res;
  FLAG_V = VFLAG_CLEAR;
}