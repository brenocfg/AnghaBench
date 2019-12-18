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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ _gxfinished ; 
 int /*<<< orphan*/  _gxwaitfinish ; 

void GX_DrawDone()
{
	u32 level;

	_CPU_ISR_Disable(level);
	GX_LOAD_BP_REG(0x45000002); // set draw done!
	GX_Flush();

	_gxfinished = 0;
	_CPU_ISR_Flash(level);

	while(!_gxfinished)
		LWP_ThreadSleep(_gxwaitfinish);
	_CPU_ISR_Restore(level);
}