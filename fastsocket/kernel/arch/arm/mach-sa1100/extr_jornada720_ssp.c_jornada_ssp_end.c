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
 int /*<<< orphan*/  GPIO_GPIO25 ; 
 int /*<<< orphan*/  GPSR ; 
 int /*<<< orphan*/  jornada_ssp_flags ; 
 int /*<<< orphan*/  jornada_ssp_lock ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void jornada_ssp_end(void)
{
	GPSR = GPIO_GPIO25;
	spin_unlock_irqrestore(&jornada_ssp_lock, jornada_ssp_flags);
	return;
}