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
struct mips_address_info {scalar_t__ type; scalar_t__ reg; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ADDRESS_REG ; 
 scalar_t__ mips_classify_address (struct mips_address_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stack_pointer_rtx ; 

bool
mips_stack_address_p (rtx x, enum machine_mode mode)
{
  struct mips_address_info addr;

  return (mips_classify_address (&addr, x, mode, false)
	  && addr.type == ADDRESS_REG
	  && addr.reg == stack_pointer_rtx);
}