#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PROTOCOL_ID_IPSEC_ESP ; 
 int /*<<< orphan*/ * IkeNewDeletePayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  NewListSingle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendInformationalExchangePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SendDeleteIPsecSaPacket(IKE_SERVER *ike, IKE_CLIENT *c, UINT spi)
{
	IKE_PACKET_PAYLOAD *payload;
	BUF *buf;
	// Validate arguments
	if (ike == NULL || c == NULL || spi == 0)
	{
		return;
	}

	buf = NewBuf();
	WriteBufInt(buf, spi);

	payload = IkeNewDeletePayload(IKE_PROTOCOL_ID_IPSEC_ESP, NewListSingle(buf));

	SendInformationalExchangePacket(ike, c, payload);
}