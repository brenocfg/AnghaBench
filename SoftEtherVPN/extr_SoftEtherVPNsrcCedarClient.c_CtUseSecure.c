#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  UseSecureDeviceId; } ;
struct TYPE_6__ {int /*<<< orphan*/  DeviceId; } ;
typedef  TYPE_1__ RPC_USE_SECURE ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_2__*) ; 

bool CtUseSecure(CLIENT *c, RPC_USE_SECURE *sec)
{
	// Validate arguments
	if (c == NULL || sec == NULL)
	{
		return false;
	}

// Do not check whether there is the specified device on the client manager
/*	if (CheckSecureDeviceId(sec->DeviceId))
	{
		c->UseSecureDeviceId = sec->DeviceId;
	}
	else
	{
		CiSetError(c, ERR_OBJECT_NOT_FOUND);
		return false;
	}
*/
	c->UseSecureDeviceId = sec->DeviceId;

	CiSaveConfigurationFile(c);

	return true;
}