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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_SIZE ; 
 int /*<<< orphan*/  IPC_ENOHEAP ; 
 int /*<<< orphan*/  IPC_OK ; 
 scalar_t__ hId ; 
 scalar_t__ iosCreateHeap (int /*<<< orphan*/ ) ; 

s32 USBKeyboard_Initialize(void)
{
	if (hId > 0)
		return 0;

	hId = iosCreateHeap(HEAP_SIZE);

	if (hId < 0)
		return IPC_ENOHEAP;

	return IPC_OK;
}