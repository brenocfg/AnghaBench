#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int Size; scalar_t__ Buf; } ;
struct TYPE_9__ {scalar_t__ ProtocolId; int /*<<< orphan*/  SpiList; } ;
struct TYPE_8__ {int /*<<< orphan*/ * IkeClient; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_1__ IKE_SA ;
typedef  TYPE_2__ IKE_PACKET_DELETE_PAYLOAD ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 TYPE_1__* FindIkeSaByResponderCookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IKE_PROTOCOL_ID_IKE ; 
 scalar_t__ IKE_PROTOCOL_ID_IPSEC_ESP ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkIPsecSaAsDeleted (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkIkeSaAsDeleted (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ READ_UINT (scalar_t__) ; 
 int /*<<< orphan*/  READ_UINT64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SearchIPsecSaBySpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void ProcDeletePayload(IKE_SERVER *ike, IKE_CLIENT *c, IKE_PACKET_DELETE_PAYLOAD *d)
{
	// Validate arguments
	if (ike == NULL || c == NULL || d == NULL)
	{
		return;
	}

	if (d->ProtocolId == IKE_PROTOCOL_ID_IPSEC_ESP)
	{
		UINT i;
		// Remove the IPsec SA
		for (i = 0;i < LIST_NUM(d->SpiList);i++)
		{
			BUF *b = LIST_DATA(d->SpiList, i);

			if (b->Size == 4)
			{
				UINT spi = READ_UINT(b->Buf);
				MarkIPsecSaAsDeleted(ike, SearchIPsecSaBySpi(ike, c, spi));
			}
		}
	}
	else if (d->ProtocolId == IKE_PROTOCOL_ID_IKE)
	{
		UINT i;
		// Remove the IKE SA
		for (i = 0;i < LIST_NUM(d->SpiList);i++)
		{
			BUF *b = LIST_DATA(d->SpiList, i);

			if (b->Size == 16)
			{
				UINT64 v1 = READ_UINT64(((UCHAR *)b->Buf) + 0);
				UINT64 v2 = READ_UINT64(((UCHAR *)b->Buf) + 8);

				IKE_SA *sa = FindIkeSaByResponderCookie(ike, v2);

				if (sa != NULL && sa->IkeClient == c)
				{
					MarkIkeSaAsDeleted(ike, sa);
				}
			}
		}
	}
}