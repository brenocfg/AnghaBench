#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  DeviceList; } ;
typedef  TYPE_1__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  ElCompareDevice ; 
 int /*<<< orphan*/  ElLoadConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  ElSaveConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 

void ElInitConfig(EL *e)
{
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	// Device list initialization
	e->DeviceList = NewList(ElCompareDevice);

	// Read configuration file
	ElLoadConfig(e);

	// Write configuration file
	ElSaveConfig(e);
}