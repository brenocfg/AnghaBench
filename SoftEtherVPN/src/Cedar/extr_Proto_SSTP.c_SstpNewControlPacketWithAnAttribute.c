#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_4__ {int /*<<< orphan*/  AttributeList; } ;
typedef  TYPE_1__ SSTP_PACKET ;
typedef  int /*<<< orphan*/  SSTP_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* SstpNewControlPacket (int /*<<< orphan*/ ) ; 

SSTP_PACKET *SstpNewControlPacketWithAnAttribute(USHORT message_type, SSTP_ATTRIBUTE *a)
{
	SSTP_PACKET *p = SstpNewControlPacket(message_type);

	if (a != NULL)
	{
		Add(p->AttributeList, a);
	}

	return p;
}