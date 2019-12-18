#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ IKE_PACKET_DATA_PAYLOAD ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  MemToBuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool IkeParseDataPayload(IKE_PACKET_DATA_PAYLOAD *t, BUF *b)
{
	// Validate arguments
	if (t == NULL || b == NULL)
	{
		return false;
	}

	t->Data = MemToBuf(b->Buf, b->Size);

	return true;
}