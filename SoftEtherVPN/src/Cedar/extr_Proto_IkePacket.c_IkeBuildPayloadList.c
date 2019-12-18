#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
typedef  scalar_t__ USHORT ;
typedef  int UINT ;
struct TYPE_16__ {int Size; TYPE_2__* Buf; } ;
struct TYPE_15__ {int /*<<< orphan*/  PayloadSize; int /*<<< orphan*/  NextPayload; } ;
struct TYPE_14__ {int /*<<< orphan*/  PayloadType; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_2__ IKE_COMMON_HEADER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  IKE_PAYLOAD_NONE ; 
 TYPE_3__* IkeBuildPayload (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

BUF *IkeBuildPayloadList(LIST *o)
{
	BUF *b;
	UINT i;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	for (i = 0;i < LIST_NUM(o);i++)
	{
		IKE_PACKET_PAYLOAD *p = LIST_DATA(o, i);
		IKE_PACKET_PAYLOAD *next = NULL;
		IKE_COMMON_HEADER h;
		BUF *tmp;

		if (i < (LIST_NUM(o) - 1))
		{
			next = LIST_DATA(o, i + 1);
		}

		Zero(&h, sizeof(h));
		if (next != NULL)
		{
			h.NextPayload = next->PayloadType;
		}
		else
		{
			h.NextPayload = IKE_PAYLOAD_NONE;
		}

		tmp = IkeBuildPayload(p);
		if (tmp != NULL)
		{
			h.PayloadSize = Endian16(tmp->Size + (USHORT)sizeof(h));

			WriteBuf(b, &h, sizeof(h));
			WriteBuf(b, tmp->Buf, tmp->Size);

			FreeBuf(tmp);
		}
	}

	SeekBuf(b, 0, 0);

	return b;
}