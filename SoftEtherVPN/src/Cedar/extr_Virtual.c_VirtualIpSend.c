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
struct TYPE_4__ {int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/  VirtualLayer2Send (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__) ; 

void VirtualIpSend(VH *v, UCHAR *dest_mac, void *data, UINT size)
{
	// Validate arguments
	if (v == NULL || dest_mac == NULL || data == NULL || size == 0)
	{
		return;
	}

	// Transmission
	VirtualLayer2Send(v, dest_mac, v->MacAddress, MAC_PROTO_IPV4, data, size);
}