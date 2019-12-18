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
struct mips_address_info {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int mips_classify_address (struct mips_address_info*,int /*<<< orphan*/ ,int,int) ; 

bool
mips_legitimate_address_p (enum machine_mode mode, rtx x, int strict)
{
  struct mips_address_info addr;

  return mips_classify_address (&addr, x, mode, strict);
}