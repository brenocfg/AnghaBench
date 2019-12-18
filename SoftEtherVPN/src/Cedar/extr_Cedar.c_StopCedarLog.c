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
 int /*<<< orphan*/  FreeLog (int /*<<< orphan*/ *) ; 
 scalar_t__ Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cedar_log ; 
 int /*<<< orphan*/ * cedar_log_ref ; 

void StopCedarLog()
{
	if (cedar_log_ref == NULL)
	{
		return;
	}

	if (Release(cedar_log_ref) == 0)
	{
		FreeLog(cedar_log);
		cedar_log = NULL;
		cedar_log_ref = NULL;
	}
}