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
 int /*<<< orphan*/  callBootloader_1x (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileHandle ; 

__attribute__((used)) static void bootloaderJump(void)
{
	callBootloader_1x(0x00000000, fileHandle);
}