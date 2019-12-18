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
 scalar_t__ COMPARISON_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
conditions_mutex_p (rtx cond1, rtx cond2)
{
  if (COMPARISON_P (cond1)
      && COMPARISON_P (cond2)
      && GET_CODE (cond1) == reversed_comparison_code (cond2, NULL)
      && XEXP (cond1, 0) == XEXP (cond2, 0)
      && XEXP (cond1, 1) == XEXP (cond2, 1))
    return 1;
  return 0;
}