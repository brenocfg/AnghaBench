#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  echo_data ;
struct TYPE_11__ {int DataSize; int /*<<< orphan*/  Data; } ;
struct TYPE_10__ {int IsControl; TYPE_7__* Lcp; int /*<<< orphan*/  Protocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  NextId; } ;
typedef  TYPE_1__ PPP_SESSION ;
typedef  TYPE_2__ PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (char*,int) ; 
 int /*<<< orphan*/  FreePPPPacket (TYPE_2__*) ; 
 TYPE_7__* NewPPPLCP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPPSendPacket (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PPP_LCP_CODE_ECHO_REQUEST ; 
 int /*<<< orphan*/  PPP_PROTOCOL_LCP ; 
 TYPE_2__* ZeroMalloc (int) ; 

void PPPSendEchoRequest(PPP_SESSION *p)
{
	PPP_PACKET *pp;
	char echo_data[]= "\0\0\0\0Aho Baka Manuke";
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	pp = ZeroMalloc(sizeof(PPP_PACKET));
	pp->Protocol = PPP_PROTOCOL_LCP;
	pp->IsControl = true;
	pp->Lcp = NewPPPLCP(PPP_LCP_CODE_ECHO_REQUEST, p->NextId++);

	pp->Lcp->Data = Clone(echo_data, sizeof(echo_data));
	pp->Lcp->DataSize = sizeof(echo_data);

	PPPSendPacket(p, pp);

	FreePPPPacket(pp);
}