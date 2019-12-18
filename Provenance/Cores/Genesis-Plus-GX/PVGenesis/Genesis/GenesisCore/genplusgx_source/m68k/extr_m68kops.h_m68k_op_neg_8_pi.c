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
 int EA_AY_PI_8 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int FLAG_V ; 
 int /*<<< orphan*/  FLAG_X ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_8 (int) ; 
 int /*<<< orphan*/  NFLAG_8 (int) ; 
 int m68ki_read_8 (int) ; 
 int /*<<< orphan*/  m68ki_write_8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_neg_8_pi(void)
{
  uint ea = EA_AY_PI_8();
  uint src = m68ki_read_8(ea);
  uint res = 0 - src;

  FLAG_N = NFLAG_8(res);
  FLAG_C = FLAG_X = CFLAG_8(res);
  FLAG_V = src & res;
  FLAG_Z = MASK_OUT_ABOVE_8(res);

  m68ki_write_8(ea, FLAG_Z);
}