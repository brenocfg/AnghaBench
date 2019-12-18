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
struct TYPE_4__ {struct TYPE_4__* Data; int /*<<< orphan*/ * AttributeList; } ;
typedef  TYPE_1__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  SstpFreeAttributeList (int /*<<< orphan*/ *) ; 

void SstpFreePacket(SSTP_PACKET *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->AttributeList != NULL)
	{
		SstpFreeAttributeList(p->AttributeList);
	}

	if (p->Data != NULL)
	{
		Free(p->Data);
	}

	Free(p);
}