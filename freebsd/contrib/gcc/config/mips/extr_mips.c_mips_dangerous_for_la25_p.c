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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ TARGET_EXPLICIT_RELOCS ; 
 int /*<<< orphan*/  VOIDmode ; 
 int global_got_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
mips_dangerous_for_la25_p (rtx x)
{
  HOST_WIDE_INT offset;

  if (TARGET_EXPLICIT_RELOCS)
    return false;

  mips_split_const (x, &x, &offset);
  return global_got_operand (x, VOIDmode);
}