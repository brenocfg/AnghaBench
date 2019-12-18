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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 void* MallocEx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (void*,int /*<<< orphan*/ ) ; 

void *ZeroMallocEx(UINT size, bool zero_clear_when_free)
{
	void *p = MallocEx(size, zero_clear_when_free);
	Zero(p, size);
	return p;
}