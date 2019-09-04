#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  UseSecureDeviceId; } ;
struct TYPE_5__ {int /*<<< orphan*/  DeviceId; } ;
typedef  TYPE_1__ RPC_USE_SECURE ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */

bool CtGetUseSecure(CLIENT *c, RPC_USE_SECURE *sec)
{
	// Validate arguments
	if (c == NULL || sec == NULL)
	{
		return false;
	}

	sec->DeviceId = c->UseSecureDeviceId;

	return true;
}