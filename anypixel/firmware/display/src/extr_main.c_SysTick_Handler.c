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
 int /*<<< orphan*/  LocalTime ; 
 scalar_t__ SYSTEMTICK_PERIOD_MS ; 
 int /*<<< orphan*/  TLC59401_Update () ; 

void SysTick_Handler(void)
{
  /* Update the LocalTime by adding SYSTEMTICK_PERIOD_MS each SysTick interrupt */
    LocalTime += SYSTEMTICK_PERIOD_MS;
    TLC59401_Update();
}