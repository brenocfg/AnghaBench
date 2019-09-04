#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int IsEnabled; int /*<<< orphan*/  DDnsTriggerInt; } ;
typedef  TYPE_1__ AZURE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AcApplyCurrentConfig (TYPE_1__*,int /*<<< orphan*/ *) ; 

void AcSetEnable(AZURE_CLIENT *ac, bool enabled)
{
	bool old_status;
	// Validate arguments
	if (ac == NULL)
	{
		return;
	}

	old_status = ac->IsEnabled;

	ac->IsEnabled = enabled;

	if (ac->IsEnabled && (ac->IsEnabled != old_status))
	{
		ac->DDnsTriggerInt++;
	}

	AcApplyCurrentConfig(ac, NULL);
}