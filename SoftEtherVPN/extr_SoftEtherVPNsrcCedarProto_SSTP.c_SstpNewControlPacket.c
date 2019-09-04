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
struct TYPE_4__ {int IsControl; int /*<<< orphan*/  AttributeList; int /*<<< orphan*/  Version; int /*<<< orphan*/  MessageType; } ;
typedef  TYPE_1__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSTP_VERSION_1 ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSTP_PACKET *SstpNewControlPacket(USHORT message_type)
{
	SSTP_PACKET *p = ZeroMalloc(sizeof(SSTP_PACKET));

	p->IsControl = true;
	p->MessageType = message_type;
	p->Version = SSTP_VERSION_1;
	p->AttributeList = NewListFast(NULL);

	return p;
}