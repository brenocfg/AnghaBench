#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  IvRecv; int /*<<< orphan*/  IvSend; void* KeyId; int /*<<< orphan*/  SendControlPacketList; int /*<<< orphan*/  AckReplyList; int /*<<< orphan*/  Status; int /*<<< orphan*/  Server; TYPE_1__* Session; } ;
struct TYPE_6__ {void* LastCreatedChannelIndex; int /*<<< orphan*/  Server; } ;
typedef  TYPE_1__ OPENVPN_SESSION ;
typedef  TYPE_2__ OPENVPN_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  NewIntList (int) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENVPN_CHANNEL_STATUS_INIT ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

OPENVPN_CHANNEL *OvsNewChannel(OPENVPN_SESSION *se, UCHAR key_id)
{
	OPENVPN_CHANNEL *c;
	// Validate arguments
	if (se == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(OPENVPN_CHANNEL));

	c->Session = se;
	c->Server = se->Server;

	c->Status = OPENVPN_CHANNEL_STATUS_INIT;

	c->AckReplyList = NewIntList(true);

	c->SendControlPacketList = NewListFast(NULL);

	c->KeyId = key_id;

	Rand(c->IvSend, sizeof(c->IvSend));
	Rand(c->IvRecv, sizeof(c->IvRecv));

	//c->NextRekey = se->Server->Now + (UINT64)5000;

	se->LastCreatedChannelIndex = key_id;

	return c;
}