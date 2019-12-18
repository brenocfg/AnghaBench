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
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_min_alignment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsettable_memref_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 

int
sparc_splitdi_legitimate (rtx reg, rtx mem)
{
  /* Punt if we are here by mistake.  */
  gcc_assert (reload_completed);

  /* We must have an offsettable memory reference.  */
  if (! offsettable_memref_p (mem))
    return 0;

  /* If we have legitimate args for ldd/std, we do not want
     the split to happen.  */
  if ((REGNO (reg) % 2) == 0
      && mem_min_alignment (mem, 8))
    return 0;

  /* Success.  */
  return 1;
}