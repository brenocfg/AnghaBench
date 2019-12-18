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
struct likely_spilled_retval_info {unsigned int regno; unsigned int nregs; unsigned int mask; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int** hard_regno_nregs ; 

__attribute__((used)) static void
likely_spilled_retval_1 (rtx x, rtx set, void *data)
{
  struct likely_spilled_retval_info *info = data;
  unsigned regno, nregs;
  unsigned new_mask;

  if (!REG_P (XEXP (set, 0)))
    return;
  regno = REGNO (x);
  if (regno >= info->regno + info->nregs)
    return;
  nregs = hard_regno_nregs[regno][GET_MODE (x)];
  if (regno + nregs <= info->regno)
    return;
  new_mask = (2U << (nregs - 1)) - 1;
  if (regno < info->regno)
    new_mask >>= info->regno - regno;
  else
    new_mask <<= regno - info->regno;
  info->mask &= new_mask;
}