#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int IgnoreSendErr; } ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {TYPE_3__* UdpSock; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  SharedSecret; } ;
typedef  int /*<<< orphan*/  RADIUS_PACKET ;
typedef  TYPE_1__ EAP_CLIENT ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* GenerateRadiusPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SendTo (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool EapSendPacket(EAP_CLIENT *e, RADIUS_PACKET *r)
{
	BUF *b;
	bool ret = false;
	if (e == NULL || r == NULL)
	{
		return false;
	}

	b = GenerateRadiusPacket(r, e->SharedSecret);
	if (b != NULL)
	{
		UINT r = SendTo(e->UdpSock, &e->ServerIp, e->ServerPort, b->Buf, b->Size);
		if (!(r == 0 && e->UdpSock->IgnoreSendErr == false))
		{
			ret = true;
		}


		FreeBuf(b);
	}

	return ret;
}