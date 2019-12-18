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
typedef  int /*<<< orphan*/  FCEUGI ;

/* Variables and functions */
 int /*<<< orphan*/  CloseStuff ; 
 scalar_t__ InitJoysticks () ; 
 int /*<<< orphan*/  InitKeyboard () ; 
 int /*<<< orphan*/  InitOtherInput () ; 
 scalar_t__ InitSound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitVideo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSignals (int /*<<< orphan*/ ) ; 
 int inited ; 

__attribute__((used)) static int DriverInitialize(FCEUGI *gi)
{
	#ifndef WIN32
	SetSignals(CloseStuff);
	#endif

	/* Initialize video before all else, due to some wacko dependencies
	   in the SexyAL code(DirectSound) that need to be fixed.
	*/

        if(!InitVideo(gi)) return 0;
        inited|=4;

	if(InitSound(gi))
	 inited|=1;

	if(InitJoysticks())
	 inited|=2;

	if(!InitKeyboard()) return 0;
	inited|=8;

	InitOtherInput();
	return 1;
}