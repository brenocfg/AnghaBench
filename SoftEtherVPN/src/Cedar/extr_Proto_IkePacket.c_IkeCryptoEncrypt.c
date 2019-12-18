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
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/  AesKey; int /*<<< orphan*/  DesKey3; int /*<<< orphan*/  DesKey2; int /*<<< orphan*/  DesKey1; TYPE_1__* Crypto; } ;
struct TYPE_4__ {int BlockSize; int CryptoId; } ;
typedef  TYPE_2__ IKE_CRYPTO_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  AesEncrypt (void*,void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  Des3Encrypt2 (void*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  DesEncrypt (void*,void*,int,int /*<<< orphan*/ ,void*) ; 
#define  IKE_CRYPTO_3DES_ID 130 
#define  IKE_CRYPTO_AES_ID 129 
#define  IKE_CRYPTO_DES_ID 128 
 int /*<<< orphan*/  Zero (void*,int) ; 

void IkeCryptoEncrypt(IKE_CRYPTO_KEY *k, void *dst, void *src, UINT size, void *ivec)
{
	// Validate arguments
	if (k == NULL || dst == NULL || src == NULL || size == 0 || ivec == NULL)
	{
		Zero(dst, size);
		return;
	}

	if ((size % k->Crypto->BlockSize) != 0)
	{
		Zero(dst, size);
		return;
	}

	switch (k->Crypto->CryptoId)
	{
	case IKE_CRYPTO_DES_ID:		// DES
		DesEncrypt(dst, src, size, k->DesKey1, ivec);
		break;

	case IKE_CRYPTO_3DES_ID:	// 3DES
		Des3Encrypt2(dst, src, size, k->DesKey1, k->DesKey2, k->DesKey3, ivec);
		break;

	case IKE_CRYPTO_AES_ID:		// AES
		AesEncrypt(dst, src, size, k->AesKey, ivec);
		break;

	default:
		// Unknown
		Zero(dst, size);
		break;
	}
}