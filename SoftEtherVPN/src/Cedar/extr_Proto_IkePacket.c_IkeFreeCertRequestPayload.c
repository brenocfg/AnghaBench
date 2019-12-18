#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * Data; } ;
typedef  TYPE_1__ IKE_PACKET_CERT_REQUEST_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 

void IkeFreeCertRequestPayload(IKE_PACKET_CERT_REQUEST_PAYLOAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (t->Data != NULL)
	{
		FreeBuf(t->Data);
		t->Data = NULL;
	}
}