#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_13__ {scalar_t__ Protocol; int /*<<< orphan*/  lock; TYPE_1__* Udp; } ;
struct TYPE_12__ {int /*<<< orphan*/  Cancel1; TYPE_4__* Connection; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int port; int /*<<< orphan*/  ip; TYPE_2__* s; } ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ SESSION ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ CONNECTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ CONNECTION_UDP ; 
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,int) ; 
 int /*<<< orphan*/  Endian32 (int) ; 
 TYPE_3__* GetSessionFromUDPEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutUDPPacketData (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void UDPReceivedPacket(CEDAR *cedar, SOCK *s, IP *ip, UINT port, void *data, UINT size)
{
	SESSION *session;
	UINT *key32;
	UCHAR *buf;
	CONNECTION *c;
	// Validate arguments
	if (s == NULL || ip == NULL || data == NULL || size == 0 || cedar == NULL)
	{
		return;
	}

	if (size < 16)
	{
		// Ignore since the packet size is not enough
		return;
	}
	buf = (UCHAR *)data;
	key32 = (UINT *)(buf + 4);


	// Get the session from the Key32 value
	session = GetSessionFromUDPEntry(cedar, Endian32(*key32));
	if (session == NULL)
	{
		Debug("Invalid UDP Session Key 32: 0x%X\n", *key32);
		return;
	}

	c = session->Connection;

	// Write the data
	PutUDPPacketData(c, buf, size);

	// Rewrite the UDP socket associated with the connection
	Lock(c->lock);
	{
		if (c->Protocol == CONNECTION_UDP)
		{
			if (c->Udp->s != s)
			{
				if (c->Udp->s != NULL)
				{
					ReleaseSock(c->Udp->s);
				}
				AddRef(s->ref);
				c->Udp->s = s;
			}
			Copy(&c->Udp->ip, ip, sizeof(UINT));
			c->Udp->port = port;
		}
	}
	Unlock(c->lock);

	// Invoke the Cancel
	Cancel(session->Cancel1);

	// Release the session
	ReleaseSession(session);
}