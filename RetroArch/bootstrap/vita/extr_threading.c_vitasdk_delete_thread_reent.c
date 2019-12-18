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
 int __vita_delete_thread_reent (int) ; 
 int /*<<< orphan*/  _newlib_reent_mutex ; 
 int /*<<< orphan*/  sceKernelLockMutex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceKernelUnlockMutex (int /*<<< orphan*/ ,int) ; 

int vitasdk_delete_thread_reent(int thid)
{
	int res = 0;
	// Lock the list because we'll be modifying it
	sceKernelLockMutex(_newlib_reent_mutex, 1, NULL);

	res = __vita_delete_thread_reent(thid);

	sceKernelUnlockMutex(_newlib_reent_mutex, 1);
	return res;
}