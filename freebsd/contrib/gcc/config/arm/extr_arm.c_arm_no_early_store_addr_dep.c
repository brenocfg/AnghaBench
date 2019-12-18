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
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
arm_no_early_store_addr_dep (rtx producer, rtx consumer)
{
  rtx value = PATTERN (producer);
  rtx addr = PATTERN (consumer);

  if (GET_CODE (value) == COND_EXEC)
    value = COND_EXEC_CODE (value);
  if (GET_CODE (value) == PARALLEL)
    value = XVECEXP (value, 0, 0);
  value = XEXP (value, 0);
  if (GET_CODE (addr) == COND_EXEC)
    addr = COND_EXEC_CODE (addr);
  if (GET_CODE (addr) == PARALLEL)
    addr = XVECEXP (addr, 0, 0);
  addr = XEXP (addr, 0);

  return !reg_overlap_mentioned_p (value, addr);
}