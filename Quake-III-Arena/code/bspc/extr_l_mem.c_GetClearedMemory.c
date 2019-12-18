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
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MemorySize (void*) ; 
 int /*<<< orphan*/  allocedmemory ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void *GetClearedMemory(int size)
{
	void *ptr;

	ptr = (void *) malloc(size);
	if (!ptr) Error("out of memory");
	memset(ptr, 0, size);
	allocedmemory += MemorySize(ptr);
	return ptr;
}