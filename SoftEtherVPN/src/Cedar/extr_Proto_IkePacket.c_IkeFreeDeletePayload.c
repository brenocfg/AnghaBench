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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * SpiList; } ;
typedef  TYPE_1__ IKE_PACKET_DELETE_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void IkeFreeDeletePayload(IKE_PACKET_DELETE_PAYLOAD *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (t->SpiList != NULL)
	{
		for (i = 0;i < LIST_NUM(t->SpiList);i++)
		{
			BUF *spi = LIST_DATA(t->SpiList, i);

			FreeBuf(spi);
		}

		ReleaseList(t->SpiList);

		t->SpiList = NULL;
	}
}