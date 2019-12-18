#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSoundUpdate (int /*<<< orphan*/ ,int) ; 
 int EOPT_NO_FRMLIMIT ; 
 int PicoSkipFrame ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  sndbuff ; 

__attribute__((used)) static void update_sound(int len)
{
	/* avoid writing audio when lagging behind to prevent audio lag */
	if (PicoSkipFrame != 2)
		DSoundUpdate(sndbuff, (currentConfig.EmuOpt & EOPT_NO_FRMLIMIT) ? 0 : 1);
}