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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;

/* Variables and functions */
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  gen_rtx_HIGH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_force_temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* mips_split_p ; 
 int /*<<< orphan*/  mips_unspec_address (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
mips_unspec_offset_high (rtx temp, rtx base, rtx addr,
			 enum mips_symbol_type symbol_type)
{
  if (mips_split_p[symbol_type])
    {
      addr = gen_rtx_HIGH (Pmode, mips_unspec_address (addr, symbol_type));
      addr = mips_force_temporary (temp, addr);
      return mips_force_temporary (temp, gen_rtx_PLUS (Pmode, addr, base));
    }
  return base;
}