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
struct TYPE_8__ {int /*<<< orphan*/  LastRecvTime; int /*<<< orphan*/  TubeRecv; } ;
struct TYPE_7__ {int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ TUBEDATA ;
typedef  TYPE_2__ PPP_SESSION ;
typedef  int /*<<< orphan*/  PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  FreeTubeData (TYPE_1__*) ; 
 int /*<<< orphan*/  PPP_PACKET_RECV_TIMEOUT ; 
 int /*<<< orphan*/ * ParsePPPPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_1__* TubeRecvAsync (int /*<<< orphan*/ ) ; 
 TYPE_1__* TubeRecvSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PPP_PACKET *PPPRecvPacket(PPP_SESSION *p, bool async)
{
	TUBEDATA *d;
	PPP_PACKET *pp;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

LABEL_LOOP:

	if (async == false)
	{
		d = TubeRecvSync(p->TubeRecv, PPP_PACKET_RECV_TIMEOUT);
	}
	else
	{
		d = TubeRecvAsync(p->TubeRecv);
	}

	if (d == NULL)
	{
		return NULL;
	}

	pp = ParsePPPPacket(d->Data, d->DataSize);
	FreeTubeData(d);

	if (pp == NULL)
	{
		// A broken packet is received
		goto LABEL_LOOP;
	}

	p->LastRecvTime = Tick64();

	return pp;
}