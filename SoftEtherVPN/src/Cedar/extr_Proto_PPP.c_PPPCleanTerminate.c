#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {scalar_t__ Code; } ;
struct TYPE_14__ {int IsControl; scalar_t__ Protocol; TYPE_9__* Lcp; } ;
struct TYPE_13__ {TYPE_10__* TubeRecv; int /*<<< orphan*/  NextId; } ;
struct TYPE_12__ {int /*<<< orphan*/  Event; } ;
typedef  TYPE_1__ PPP_SESSION ;
typedef  TYPE_2__ PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  FreePPPPacket (TYPE_2__*) ; 
 int IsTubeConnected (TYPE_10__*) ; 
 TYPE_9__* NewPPPLCP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* PPPRecvPacket (TYPE_1__*,int) ; 
 int PPPSendPacket (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ PPP_LCP_CODE_TERMINATE_ACK ; 
 int /*<<< orphan*/  PPP_LCP_CODE_TERMINATE_REQ ; 
 scalar_t__ PPP_PROTOCOL_LCP ; 
 scalar_t__ PPP_TERMINATE_TIMEOUT ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void PPPCleanTerminate(PPP_SESSION *p)
{
	PPP_PACKET *pp;
	PPP_PACKET *res;
	UINT64 giveup_tick = Tick64() + (UINT64)PPP_TERMINATE_TIMEOUT;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	// Send a Terminate Request
	pp = ZeroMalloc(sizeof(PPP_PACKET));
	pp->IsControl = true;
	pp->Protocol = PPP_PROTOCOL_LCP;
	pp->Lcp = NewPPPLCP(PPP_LCP_CODE_TERMINATE_REQ, p->NextId++);
	Debug("PPP: Terminate Request is Sent.\n");
	if (PPPSendPacket(p, pp) == false)
	{
		goto LABEL_CLEANUP;
	}

	// Wait for Terminate ACK
	while (true)
	{
		UINT64 now = Tick64();
		UINT interval;

		if (now >= giveup_tick)
		{
			break;
		}

		while (true)
		{
			if (IsTubeConnected(p->TubeRecv) == false)
			{
				break;
			}

			res = PPPRecvPacket(p, true);

			if (res == NULL)
			{
				break;
			}

			if (res->IsControl && res->Protocol == PPP_PROTOCOL_LCP && res->Lcp->Code == PPP_LCP_CODE_TERMINATE_ACK)
			{
				Debug("PPP: Terminate ACK is Received.\n");
				FreePPPPacket(res);
				goto LABEL_CLEANUP;
			}

			FreePPPPacket(res);
		}

		interval = (UINT)(giveup_tick - now);

		Wait(p->TubeRecv->Event, interval);
	}

LABEL_CLEANUP:
	FreePPPPacket(pp);
}