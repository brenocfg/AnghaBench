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
struct TYPE_4__ {scalar_t__ TypeL3; } ;
typedef  TYPE_1__ PKT ;
typedef  int /*<<< orphan*/  NATIVE_NAT ;

/* Variables and functions */
 scalar_t__ L3_IPV4 ; 
 int /*<<< orphan*/  NnFragmentedIpReceived (int /*<<< orphan*/ *,TYPE_1__*) ; 

void NnLayer2(NATIVE_NAT *t, PKT *packet)
{
	// Validate arguments
	if (t == NULL || packet == NULL)
	{
		return;
	}

	if (packet->TypeL3 == L3_IPV4)
	{
		// IPv4
		NnFragmentedIpReceived(t, packet);
	}
}