#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* pkey; } ;
struct TYPE_7__ {TYPE_1__* rsa; } ;
struct TYPE_8__ {TYPE_2__ pkey; } ;
struct TYPE_6__ {int /*<<< orphan*/ * n; } ;
typedef  TYPE_4__ K ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BigNumToBuf (int /*<<< orphan*/ *) ; 

BUF *RsaPublicToBuf(K *k)
{
	BUF *b;
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	RSA *rsa;
	const BIGNUM *n;
#endif
	// Validate arguments
	if (k == NULL || k->pkey == NULL)
	{
		return NULL;
	}

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	rsa = EVP_PKEY_get0_RSA(k->pkey);
	if (rsa == NULL)
	{
		return NULL;
	}

	RSA_get0_key(rsa, &n, NULL, NULL);
	if (n == NULL)
	{
		return NULL;
	}

	b = BigNumToBuf(n);
#else
	if (k->pkey->pkey.rsa == NULL || k->pkey->pkey.rsa->n == NULL)
	{
		return NULL;
	}

	b = BigNumToBuf(k->pkey->pkey.rsa->n);
#endif

	if (b == NULL)
	{
		return NULL;
	}

	return b;
}