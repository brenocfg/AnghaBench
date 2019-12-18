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
 int INTVAL (int /*<<< orphan*/ ) ; 

int
insvdi_rshift_rlwimi_p (rtx sizeop, rtx startop, rtx shiftop)
{
  if (INTVAL (startop) > 32
      && INTVAL (startop) < 64
      && INTVAL (sizeop) > 1
      && INTVAL (sizeop) + INTVAL (startop) < 64
      && INTVAL (shiftop) > 0
      && INTVAL (sizeop) + INTVAL (shiftop) < 32
      && (64 - (INTVAL (shiftop) & 63)) >= INTVAL (sizeop))
    return 1;

  return 0;
}