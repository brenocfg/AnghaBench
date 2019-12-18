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
struct TYPE_4__ {int /*<<< orphan*/ * DecryptedPayload; int /*<<< orphan*/ * PayloadList; } ;
typedef  TYPE_1__ IKE_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreePayloadList (int /*<<< orphan*/ *) ; 

void IkeFree(IKE_PACKET *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	if (p->PayloadList != NULL)
	{
		IkeFreePayloadList(p->PayloadList);
	}

	if (p->DecryptedPayload != NULL)
	{
		FreeBuf(p->DecryptedPayload);
	}

	Free(p);
}