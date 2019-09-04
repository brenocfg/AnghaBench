#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* Data; } ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_2__ IKE_PACKET_DATA_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BUF *IkeBuildDataPayload(IKE_PACKET_DATA_PAYLOAD *t)
{
	BUF *b;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, t->Data->Buf, t->Data->Size);

	return b;
}