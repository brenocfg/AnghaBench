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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_address_nv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  eliminate_regs (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* reg_equiv_memory_loc ; 
 scalar_t__ replace_equiv_address_nv (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_varies_p (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
make_memloc (rtx ad, int regno)
{
  /* We must rerun eliminate_regs, in case the elimination
     offsets have changed.  */
  rtx tem
    = XEXP (eliminate_regs (reg_equiv_memory_loc[regno], 0, NULL_RTX), 0);

  /* If TEM might contain a pseudo, we must copy it to avoid
     modifying it when we do the substitution for the reload.  */
  if (rtx_varies_p (tem, 0))
    tem = copy_rtx (tem);

  tem = replace_equiv_address_nv (reg_equiv_memory_loc[regno], tem);
  tem = adjust_address_nv (tem, GET_MODE (ad), 0);

  /* Copy the result if it's still the same as the equivalence, to avoid
     modifying it when we do the substitution for the reload.  */
  if (tem == reg_equiv_memory_loc[regno])
    tem = copy_rtx (tem);
  return tem;
}