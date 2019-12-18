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
typedef  int /*<<< orphan*/  SceUID ;

/* Variables and functions */
 int /*<<< orphan*/  lprintf (char*,int /*<<< orphan*/ ,int) ; 
 int sceKernelSignalSema (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void psp_sem_unlock(SceUID sem)
{
	int ret = sceKernelSignalSema(sem, 1);
	if (ret < 0) lprintf("sceKernelSignalSema(%08x) failed with %08x\n", sem, ret);
}