#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int NatDoCancelFlag; TYPE_2__** TmpBuf; int /*<<< orphan*/  NatTable; scalar_t__ HaltNat; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  Now; int /*<<< orphan*/  SockEvent; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int Protocol; int DisconnectNow; } ;
typedef  TYPE_2__ NAT_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__**) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_1__*) ; 
 TYPE_2__** Malloc (int /*<<< orphan*/ ) ; 
#define  NAT_DNS 131 
#define  NAT_ICMP 130 
#define  NAT_TCP 129 
 int /*<<< orphan*/  NAT_TMPBUF_SIZE ; 
#define  NAT_UDP 128 
 int NatTransactDns (TYPE_1__*,TYPE_2__*) ; 
 int NatTransactIcmp (TYPE_1__*,TYPE_2__*) ; 
 int NatTransactTcp (TYPE_1__*,TYPE_2__*) ; 
 int NatTransactUdp (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SELECT_TIME ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_2__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void NatThreadMain(VH *v)
{
	bool halt_flag;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	v->TmpBuf = Malloc(NAT_TMPBUF_SIZE);

	while (true)
	{
		// Wait until the next event is set
		WaitSockEvent(v->SockEvent, SELECT_TIME);

		halt_flag = false;

		LockVirtual(v);
		{
			// Process on all NAT sessions
			UINT i, num;

			v->Now = Tick64();
			v->NatDoCancelFlag = false;

LIST_ELEMENT_DELETED:
			num = LIST_NUM(v->NatTable);
			for (i = 0;i < num;i++)
			{
				NAT_ENTRY *n = LIST_DATA(v->NatTable, i);

				switch (n->Protocol)
				{
				case NAT_TCP:		// TCP
					if (NatTransactTcp(v, n) == false)
					{
						goto LIST_ELEMENT_DELETED;
					}
					break;

				case NAT_UDP:		// UDP
					if (NatTransactUdp(v, n) == false)
					{
						goto LIST_ELEMENT_DELETED;
					}
					break;

				case NAT_ICMP:		// ICMP
					if (NatTransactIcmp(v, n) == false)
					{
						goto LIST_ELEMENT_DELETED;
					}
					break;

				case NAT_DNS:		// DNS
					if (NatTransactDns(v, n) == false)
					{
						goto LIST_ELEMENT_DELETED;
					}
					break;
				}
			}

			if (v->NatDoCancelFlag)
			{
				// Hit the cancel of the parent thread
				Cancel(v->Cancel);
			}

			// Halting flag check
			if (v->HaltNat)
			{
				halt_flag = true;
			}
		}
		UnlockVirtual(v);

		if (halt_flag)
		{
			// Terminate the thread by disconnecting all entries forcibly
			LockVirtual(v);
			{
				UINT num = LIST_NUM(v->NatTable);
				NAT_ENTRY **nn = ToArray(v->NatTable);
				UINT i;

				for (i = 0;i < num;i++)
				{
					NAT_ENTRY *n = nn[i];
					n->DisconnectNow = true;

					switch (n->Protocol)
					{
					case NAT_TCP:		// TCP
						NatTransactTcp(v, n);
						break;

					case NAT_UDP:		// UDP
						NatTransactUdp(v, n);
						break;

					case NAT_ICMP:		// ICMP
						NatTransactIcmp(v, n);
						break;

					case NAT_DNS:		// DNS
						NatTransactDns(v, n);
						break;
					}
				}

				Free(nn);
			}
			UnlockVirtual(v);
			break;
		}
	}

	Free(v->TmpBuf);
}