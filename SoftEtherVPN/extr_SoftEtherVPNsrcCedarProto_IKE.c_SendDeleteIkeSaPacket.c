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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PROTOCOL_ID_IKE ; 
 int /*<<< orphan*/ * IkeNewDeletePayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  NewListSingle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendInformationalExchangePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBufInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SendDeleteIkeSaPacket(IKE_SERVER *ike, IKE_CLIENT *c, UINT64 init_cookie, UINT64 resp_cookie)
{
	IKE_PACKET_PAYLOAD *payload;
	BUF *buf;
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return;
	}

	buf = NewBuf();
	WriteBufInt64(buf, init_cookie);
	WriteBufInt64(buf, resp_cookie);

	payload = IkeNewDeletePayload(IKE_PROTOCOL_ID_IKE, NewListSingle(buf));

	SendInformationalExchangePacket(ike, c, payload);
}