#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int TypeL3; struct TYPE_7__* HttpLog; int /*<<< orphan*/ * MacHeader; } ;
typedef  TYPE_1__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePacketARPv4 (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePacketIPv4 (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePacketTagVlan (TYPE_1__*) ; 
#define  L3_ARPV4 130 
#define  L3_IPV4 129 
#define  L3_TAGVLAN 128 

void FreePacket(PKT *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->MacHeader != NULL)
	{
		switch (p->TypeL3)
		{
		case L3_IPV4:
			FreePacketIPv4(p);
			break;

		case L3_ARPV4:
			FreePacketARPv4(p);
			break;

		case L3_TAGVLAN:
			FreePacketTagVlan(p);
			break;
		}
	}

	if (p->HttpLog != NULL)
	{
		Free(p->HttpLog);
	}

	Free(p);
}