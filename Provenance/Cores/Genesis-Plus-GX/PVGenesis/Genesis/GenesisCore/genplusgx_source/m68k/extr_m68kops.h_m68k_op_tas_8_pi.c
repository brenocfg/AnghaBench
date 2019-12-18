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
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int EA_AY_PI_8 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int /*<<< orphan*/  NFLAG_8 (int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int m68ki_read_8 (int) ; 
 scalar_t__ m68ki_tas_callback () ; 
 int /*<<< orphan*/  m68ki_write_8 (int,int) ; 

__attribute__((used)) static void m68k_op_tas_8_pi(void)
{
  uint ea = EA_AY_PI_8();
  uint dst = m68ki_read_8(ea);

  FLAG_Z = dst;
  FLAG_N = NFLAG_8(dst);
  FLAG_V = VFLAG_CLEAR;
  FLAG_C = CFLAG_CLEAR;

  /* The Genesis/Megadrive games Gargoyles and Ex-Mutants need the TAS writeback
       disabled in order to function properly.  Some Amiga software may also rely
       on this, but only when accessing specific addresses so additional functionality
       will be needed. */
  if (m68ki_tas_callback()) m68ki_write_8(ea, dst | 0x80);
}