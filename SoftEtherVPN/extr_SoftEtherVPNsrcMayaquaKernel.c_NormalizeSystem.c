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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  SystemToUINT64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void NormalizeSystem(SYSTEMTIME *st)
{
	UINT64 sec64;
	// Validate arguments
	if (st == NULL)
	{
		return;
	}

	sec64 = SystemToUINT64(st);
	UINT64ToSystem(st, sec64);
}