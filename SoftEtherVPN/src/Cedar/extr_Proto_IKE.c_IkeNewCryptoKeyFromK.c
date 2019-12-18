#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_HASH ;
typedef  int /*<<< orphan*/  IKE_CRYPTO_KEY ;
typedef  int /*<<< orphan*/  IKE_CRYPTO ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* IkeExpandKeySize (int /*<<< orphan*/ *,void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * IkeNewKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IKE_CRYPTO_KEY *IkeNewCryptoKeyFromK(IKE_SERVER *ike, void *k, UINT k_size, IKE_HASH *h, IKE_CRYPTO *c, UINT crypto_key_size)
{
	BUF *key_buf;
	IKE_CRYPTO_KEY *ret;
	// Validate arguments
	if (ike == NULL || k == NULL || k_size == 0 || h == NULL || c == NULL || crypto_key_size == 0)
	{
		return NULL;
	}

	key_buf = IkeExpandKeySize(h, k, k_size, crypto_key_size);
	if (key_buf == NULL)
	{
		return NULL;
	}

	ret = IkeNewKey(c, key_buf->Buf, key_buf->Size);

	FreeBuf(key_buf);

	return ret;
}