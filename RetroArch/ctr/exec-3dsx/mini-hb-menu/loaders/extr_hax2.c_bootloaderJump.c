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
typedef  int /*<<< orphan*/  memmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  argBuf ; 
 int /*<<< orphan*/  argBufLen ; 
 int /*<<< orphan*/  callBootloaderNewProcess_2x (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callBootloaderRunTitleCustom_2x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callBootloaderRunTitle_2x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callBootloader_2x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileHandle ; 
 scalar_t__ memMapBuf ; 
 int /*<<< orphan*/  targetMediatype ; 
 int targetProcess ; 
 int targetTid ; 
 scalar_t__ useMemMap ; 

__attribute__((used)) static void bootloaderJump(void)
{
	if (targetProcess == -1)
		callBootloader_2x(fileHandle, argBuf, argBufLen);
	else if (targetProcess == -2)
	{
		if (useMemMap)
			callBootloaderRunTitleCustom_2x(targetMediatype, argBuf, argBufLen, (u32)targetTid, (u32)(targetTid>>32), (memmap_t*)memMapBuf);
		else
			callBootloaderRunTitle_2x(targetMediatype, argBuf, argBufLen, (u32)targetTid, (u32)(targetTid>>32));
	}
	else
		callBootloaderNewProcess_2x(targetProcess, argBuf, argBufLen);
}