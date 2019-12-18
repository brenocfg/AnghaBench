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
 int /*<<< orphan*/  FALSE ; 
 int PAD_BUTTON_A ; 
 int PAD_ButtonsDown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD_Init () ; 
 int /*<<< orphan*/  PAD_ScanPads () ; 
 int PAD_TRIGGER_Z ; 
 int /*<<< orphan*/  SYS_HOTRESET ; 
 scalar_t__ SYS_ResetButtonDown () ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __reload () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int reload_timer ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void waitForReload()
{
	u32 level;

	PAD_Init();

	if(reload_timer > 0)
		kprintf("\n\tReloading in %d seconds\n", reload_timer/50);

	while ( 1 )
	{
		PAD_ScanPads();

		int buttonsDown = PAD_ButtonsDown(0);

		if( (buttonsDown & PAD_TRIGGER_Z) || SYS_ResetButtonDown() ||
			reload_timer == 0 )
		{
			kprintf("\n\tReload\n\n\n");
			_CPU_ISR_Disable(level);
			__reload ();
		}

		if ( buttonsDown & PAD_BUTTON_A )
		{
			kprintf("\n\tReset\n\n\n");
#if defined(HW_DOL)
			SYS_ResetSystem(SYS_HOTRESET,0,FALSE);
#else
			__reload ();
#endif
		}

		udelay(20000);
		if(reload_timer > 0)
			reload_timer--;
	}
}