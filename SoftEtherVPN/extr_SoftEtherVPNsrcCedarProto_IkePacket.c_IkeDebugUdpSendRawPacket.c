#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int FlagEncrypted; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ IKE_PACKET ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* IkeBuildEx (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NewUDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetIP (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void IkeDebugUdpSendRawPacket(IKE_PACKET *p)
{
	BUF *b;
	IP ip;
	SOCK *udp;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	p->FlagEncrypted = false;

	b = IkeBuildEx(p, NULL, true);

	if (b == NULL)
	{
		return;
	}

	Zero(&ip, sizeof(ip));
	SetIP(&ip, 1, 2, 3, 4);

	udp = NewUDP(0);

	SendTo(udp, &ip, 500, b->Buf, b->Size);

	ReleaseSock(udp);
	FreeBuf(b);
}