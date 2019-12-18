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
typedef  scalar_t__ SceUID ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_O_RDONLY ; 
 int /*<<< orphan*/  lprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  sceDisplayWaitVblankStart () ; 
 int /*<<< orphan*/  sceIoClose (scalar_t__) ; 
 scalar_t__ sceIoOpen (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 

void psp_resume_suspend(void)
{
	// for some reason file IO doesn't seem to work
	// after resume for some period of time, at least on 1.5
	SceUID fd;
	int i;
	for (i = 0; i < 30; i++) {
		fd = sceIoOpen("EBOOT.PBP", PSP_O_RDONLY, 0777);
		if (fd >= 0) break;
		sceKernelDelayThread(100 * 1024);
	}
	if (fd >= 0) sceIoClose(fd);
	sceDisplayWaitVblankStart();
	if (i < 30)
		lprintf("io resumed after %i tries\n", i);
	else {
		lprintf("io resume failed with %08x\n", fd);
		sceKernelDelayThread(500 * 1024);
	}
}