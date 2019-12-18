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

/* Variables and functions */
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_address_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_temp_slot_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
replace_equiv_address (rtx memref, rtx addr)
{
  /* change_address_1 copies the memory attribute structure without change
     and that's exactly what we want here.  */
  update_temp_slot_address (XEXP (memref, 0), addr);
  return change_address_1 (memref, VOIDmode, addr, 1);
}