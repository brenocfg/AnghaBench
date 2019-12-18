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
 int /*<<< orphan*/  for_each_rtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mark_reg_use_for_earlyclobber ; 

__attribute__((used)) static void
mark_reg_use_for_earlyclobber_1 (rtx *x, void *data)
{
  for_each_rtx (x, mark_reg_use_for_earlyclobber, data);
}