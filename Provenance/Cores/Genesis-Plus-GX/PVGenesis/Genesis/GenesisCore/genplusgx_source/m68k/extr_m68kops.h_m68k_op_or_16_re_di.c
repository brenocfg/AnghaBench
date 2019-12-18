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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int DX ; 
 int /*<<< orphan*/  EA_AY_DI_16 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int m68ki_read_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_write_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_or_16_re_di(void)
{
  uint ea = EA_AY_DI_16();
  uint res = MASK_OUT_ABOVE_16(DX | m68ki_read_16(ea));

  m68ki_write_16(ea, res);

  FLAG_N = NFLAG_16(res);
  FLAG_Z = res;
  FLAG_C = CFLAG_CLEAR;
  FLAG_V = VFLAG_CLEAR;
}