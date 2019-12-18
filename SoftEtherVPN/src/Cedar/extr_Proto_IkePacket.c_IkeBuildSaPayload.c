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
struct TYPE_7__ {int /*<<< orphan*/  PayloadList; } ;
struct TYPE_6__ {void* Situation; void* DoI; } ;
typedef  TYPE_1__ IKE_SA_HEADER ;
typedef  TYPE_2__ IKE_PACKET_SA_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 void* Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IKE_SA_DOI_IPSEC ; 
 int /*<<< orphan*/  IKE_SA_SITUATION_IDENTITY ; 
 int /*<<< orphan*/ * IkeBuildPayloadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *IkeBuildSaPayload(IKE_PACKET_SA_PAYLOAD *t)
{
	IKE_SA_HEADER h;
	BUF *ret;
	BUF *b;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.DoI = Endian32(IKE_SA_DOI_IPSEC);
	h.Situation = Endian32(IKE_SA_SITUATION_IDENTITY);

	ret = NewBuf();

	WriteBuf(ret, &h, sizeof(h));

	b = IkeBuildPayloadList(t->PayloadList);
	WriteBufBuf(ret, b);

	FreeBuf(b);

	return ret;
}