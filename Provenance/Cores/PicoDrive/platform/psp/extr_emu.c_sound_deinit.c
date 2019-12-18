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
 int /*<<< orphan*/  sceKernelDeleteSema (int) ; 
 int /*<<< orphan*/  sceKernelSignalSema (int,int) ; 
 int sound_sem ; 
 int sound_thread_exit ; 

__attribute__((used)) static void sound_deinit(void)
{
	sound_thread_exit = 1;
	sceKernelSignalSema(sound_sem, 1);
	sceKernelDeleteSema(sound_sem);
	sound_sem = -1;
}