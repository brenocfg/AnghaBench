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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int IsEtherIPOnIPsecTunnelMode; int /*<<< orphan*/  EtherIP; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_1__ IKE_CLIENT ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  EtherIPProcRecvPackets (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPsecIkeClientManageEtherIPServer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * NewBlock (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void ProcIPsecEtherIPPacketRecv(IKE_SERVER *ike, IKE_CLIENT *c, UCHAR *data, UINT data_size, bool is_tunnel_mode)
{
	BLOCK *b;
	// Validate arguments
	if (ike == NULL || c == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	c->IsEtherIPOnIPsecTunnelMode = is_tunnel_mode;

	IPsecIkeClientManageEtherIPServer(ike, c);

	b = NewBlock(data, data_size, 0);

	EtherIPProcRecvPackets(c->EtherIP, b);

	Free(b);
}