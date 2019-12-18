#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  NextIv; int /*<<< orphan*/ * Key; int /*<<< orphan*/  Iv; } ;
struct TYPE_12__ {scalar_t__ FlagEncrypted; } ;
struct TYPE_11__ {int IsIvExisting; TYPE_1__* IkeSa; struct TYPE_11__* PairIPsecSa; int /*<<< orphan*/  Iv; } ;
struct TYPE_10__ {int /*<<< orphan*/  BlockSize; int /*<<< orphan*/ * CryptoKey; } ;
typedef  TYPE_2__ IPSECSA ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_3__ IKE_PACKET ;
typedef  TYPE_4__ IKE_CRYPTO_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPsecSaUpdateIv (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* IkeParse (void*,scalar_t__,TYPE_4__*) ; 

IKE_PACKET *IPsecSaRecvPacket(IKE_SERVER *ike, IPSECSA *sa, void *data, UINT size)
{
	IKE_PACKET *ret;
	// Validate arguments
	if (ike == NULL || sa == NULL || (size != 0 && data == NULL))
	{
		return NULL;
	}

	if (sa->IsIvExisting == false || sa->IkeSa->CryptoKey == NULL)
	{
		ret = IkeParse(data, size, NULL);
	}
	else
	{
		IKE_CRYPTO_PARAM cp;

		Copy(&cp.Iv, sa->Iv, sa->IkeSa->BlockSize);
		cp.Key = sa->IkeSa->CryptoKey;

		ret = IkeParse(data, size, &cp);

		if (ret->FlagEncrypted)
		{
			IPsecSaUpdateIv(sa, cp.NextIv, sa->IkeSa->BlockSize);
			IPsecSaUpdateIv(sa->PairIPsecSa, cp.NextIv, sa->IkeSa->BlockSize);
		}
	}

	return ret;
}