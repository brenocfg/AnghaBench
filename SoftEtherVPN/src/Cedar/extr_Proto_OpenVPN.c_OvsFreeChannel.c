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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * X; } ;
struct TYPE_6__ {TYPE_1__ ClientCert; int /*<<< orphan*/  MdSend; int /*<<< orphan*/  MdRecv; int /*<<< orphan*/  CipherEncrypt; int /*<<< orphan*/  CipherDecrypt; int /*<<< orphan*/  SendControlPacketList; int /*<<< orphan*/  AckReplyList; int /*<<< orphan*/ * SslPipe; } ;
typedef  int /*<<< orphan*/  OPENVPN_CONTROL_PACKET ;
typedef  TYPE_2__ OPENVPN_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeCipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeMd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSslPipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OvsFreeControlPacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseIntList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void OvsFreeChannel(OPENVPN_CHANNEL *c)
{
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	if (c->SslPipe != NULL)
	{
		FreeSslPipe(c->SslPipe);
	}

	ReleaseIntList(c->AckReplyList);

	for (i = 0;i < LIST_NUM(c->SendControlPacketList);i++)
	{
		OPENVPN_CONTROL_PACKET *p = LIST_DATA(c->SendControlPacketList, i);

		OvsFreeControlPacket(p);
	}

	ReleaseList(c->SendControlPacketList);

	FreeCipher(c->CipherDecrypt);
	FreeCipher(c->CipherEncrypt);

	FreeMd(c->MdRecv);
	FreeMd(c->MdSend);

	if (c->ClientCert.X != NULL)
	{
		FreeX(c->ClientCert.X);
	}

	Free(c);
}