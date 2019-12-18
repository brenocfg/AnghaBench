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
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_SWITCH_DAY ; 
 int /*<<< orphan*/  NewLog (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewRef () ; 
 int /*<<< orphan*/  cedar_log ; 
 int /*<<< orphan*/ * cedar_log_ref ; 

void StartCedarLog()
{
	if (cedar_log_ref == NULL)
	{
		cedar_log_ref = NewRef();
	}
	else
	{
		AddRef(cedar_log_ref);
	}

	cedar_log = NewLog("debug_log", "debug", LOG_SWITCH_DAY);
}