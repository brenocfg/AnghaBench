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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  NatTableForRecv; scalar_t__ IsRawIpMode; } ;
typedef  int /*<<< orphan*/  NATIVE_NAT_ENTRY ;
typedef  TYPE_1__ NATIVE_NAT ;

/* Variables and functions */
 scalar_t__ NN_RAW_IP_PORT_END ; 
 scalar_t__ NN_RAW_IP_PORT_START ; 
 int /*<<< orphan*/  NnSetNat (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ Rand32 () ; 
 TYPE_1__* SearchHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

UINT NnMapNewPublicPort(NATIVE_NAT *t, UINT protocol, UINT dest_ip, UINT dest_port, UINT public_ip)
{
	UINT i;
	UINT base_port;
	UINT port_start = 1025;
	UINT port_end = 65500;
	// Validate arguments
	if (t == NULL)
	{
		return 0;
	}

	if (t->IsRawIpMode)
	{
		port_start = NN_RAW_IP_PORT_START;
		port_end = NN_RAW_IP_PORT_END;
	}

	base_port = Rand32() % (port_end - port_start) + port_start;

	for (i = 0;i < (port_end - port_start);i++)
	{
		UINT port;
		NATIVE_NAT_ENTRY tt;
		NATIVE_NAT *e;

		port = base_port + i;
		if (port > port_end)
		{
			port = port - port_end + port_start;
		}

		// Is this port vacant?
		NnSetNat(&tt, protocol, 0, 0, dest_ip, dest_port, public_ip, port);

		e = SearchHash(t->NatTableForRecv, &tt);

		if (e == NULL)
		{
			// Free port is found
			return port;
		}
	}

	return 0;
}