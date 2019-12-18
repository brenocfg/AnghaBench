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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/ * force_reg (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lowpart_subreg (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static rtx
lowpart_subreg_maybe_copy (enum machine_mode omode, rtx val,
			   enum machine_mode imode)
{
  rtx ret;
  ret = lowpart_subreg (omode, val, imode);
  if (ret == NULL)
    {
      val = force_reg (imode, val);
      ret = lowpart_subreg (omode, val, imode);
      gcc_assert (ret != NULL);
    }
  return ret;
}