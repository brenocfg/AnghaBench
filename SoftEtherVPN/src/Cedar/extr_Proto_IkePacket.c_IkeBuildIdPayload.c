#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
struct TYPE_7__ {int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  Port; int /*<<< orphan*/  IdType; } ;
struct TYPE_6__ {int /*<<< orphan*/  IdData; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  Port; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ IKE_PACKET_ID_PAYLOAD ;
typedef  TYPE_2__ IKE_ID_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

BUF *IkeBuildIdPayload(IKE_PACKET_ID_PAYLOAD *t)
{
	IKE_ID_HEADER h;
	BUF *ret;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.IdType = t->Type;
	h.Port = Endian16(t->Port);
	h.ProtocolId = t->ProtocolId;

	ret = NewBuf();
	WriteBuf(ret, &h, sizeof(h));

	WriteBufBuf(ret, t->IdData);

	return ret;
}