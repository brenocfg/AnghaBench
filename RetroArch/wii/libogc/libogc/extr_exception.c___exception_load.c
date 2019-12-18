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
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCFlushRangeNoSync (void*,size_t) ; 
 int /*<<< orphan*/  ICInvalidateRange (void*,size_t) ; 
 int /*<<< orphan*/  _sync () ; 
 int* exception_location ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void __exception_load(u32 nExc,void *data,u32 len,void *patch)
{
	void *pAddr = (void*)(0x80000000|exception_location[nExc]);
	memcpy(pAddr,data,len);
	if(patch)
		*(u32*)((u32)pAddr+(patch-data)) |= nExc;

	DCFlushRangeNoSync(pAddr,len);
	ICInvalidateRange(pAddr,len);
	_sync();
}