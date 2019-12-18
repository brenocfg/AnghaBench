#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int /*<<< orphan*/  NextIv; int /*<<< orphan*/ * Key; int /*<<< orphan*/  Iv; } ;
struct TYPE_10__ {scalar_t__ FlagEncrypted; } ;
struct TYPE_9__ {int IsIvExisting; int /*<<< orphan*/  BlockSize; int /*<<< orphan*/ * CryptoKey; int /*<<< orphan*/  Iv; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_1__ IKE_SA ;
typedef  TYPE_2__ IKE_PACKET ;
typedef  TYPE_3__ IKE_CRYPTO_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* IkeParse (void*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  IkeSaUpdateIv (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IKE_PACKET *IkeSaRecvPacket(IKE_SERVER *ike, IKE_SA *sa, void *data, UINT size)
{
	IKE_PACKET *ret;
	// Validate arguments
	if (ike == NULL || sa == NULL || (size != 0 && data == NULL))
	{
		return NULL;
	}

	if (sa->IsIvExisting == false || sa->CryptoKey == NULL)
	{
		ret = IkeParse(data, size, NULL);
	}
	else
	{
		IKE_CRYPTO_PARAM cp;

		Copy(&cp.Iv, sa->Iv, sa->BlockSize);
		cp.Key = sa->CryptoKey;

		ret = IkeParse(data, size, &cp);

		if (ret->FlagEncrypted)
		{
			IkeSaUpdateIv(sa, cp.NextIv, sa->BlockSize);
		}
	}

	return ret;
}