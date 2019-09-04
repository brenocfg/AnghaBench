#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ IsControl; } ;
struct TYPE_9__ {int /*<<< orphan*/  Now; int /*<<< orphan*/  LastRecvTick; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  TYPE_2__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  SstpProcessControlPacket (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SstpProcessDataPacket (TYPE_1__*,TYPE_2__*) ; 

void SstpProcessPacket(SSTP_SERVER *s, SSTP_PACKET *p)
{
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	s->LastRecvTick = s->Now;

	if (p->IsControl)
	{
		// Control packet
		SstpProcessControlPacket(s, p);
	}
	else
	{
		// Data packet
		SstpProcessDataPacket(s, p);
	}
}