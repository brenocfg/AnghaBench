#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * CurrentIpSecSaSend; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_1__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  IPsecSendPacketByIPsecSa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void IPsecSendPacketByIkeClient(IKE_SERVER *ike, IKE_CLIENT *c, UCHAR *data, UINT data_size, UCHAR protocol_id)
{
	// Validate arguments
	if (ike == NULL || c == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	if (c->CurrentIpSecSaSend == NULL)
	{
		return;
	}

	IPsecSendPacketByIPsecSa(ike, c->CurrentIpSecSaSend, data, data_size, protocol_id);
}