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

/* Variables and functions */
 int /*<<< orphan*/  PTW32_EPS_CANCEL ; 
 int /*<<< orphan*/  ptw32_throw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptw32_cancel_self (void)
{
  ptw32_throw (PTW32_EPS_CANCEL);

  /* Never reached */
}