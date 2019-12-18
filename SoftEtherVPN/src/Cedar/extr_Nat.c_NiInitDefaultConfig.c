#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int SaveLog; } ;
struct TYPE_5__ {int Online; TYPE_3__ Option; int /*<<< orphan*/  AdminPort; } ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_NAT_ADMIN_PORT ; 
 int /*<<< orphan*/  NiSetDefaultVhOption (TYPE_1__*,TYPE_3__*) ; 

void NiInitDefaultConfig(NAT *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	// Initialize the virtual host option
	NiSetDefaultVhOption(n, &n->Option);

	// Initialize management port
	n->AdminPort = DEFAULT_NAT_ADMIN_PORT;

	// Offline
	n->Online = false;

	// Save the log
	n->Option.SaveLog = true;
}