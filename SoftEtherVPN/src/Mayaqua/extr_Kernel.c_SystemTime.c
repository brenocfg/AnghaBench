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
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  KS_GETTIME_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSGetSystemTime (int /*<<< orphan*/ *) ; 

void SystemTime(SYSTEMTIME *st)
{
	// Validate arguments
	if (st == NULL)
	{
		return;
	}

	OSGetSystemTime(st);

	// KS
	KS_INC(KS_GETTIME_COUNT);
}