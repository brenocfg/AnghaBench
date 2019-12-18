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
 scalar_t__ ANTIC_CPU_CLOCK ; 
 int /*<<< orphan*/  POKEYSND_GenerateSync (scalar_t__) ; 
 scalar_t__ prev_update_tick ; 

__attribute__((used)) static void Update_synchronized_sound(void)
{
	POKEYSND_GenerateSync(ANTIC_CPU_CLOCK - prev_update_tick);
	prev_update_tick = ANTIC_CPU_CLOCK;
}