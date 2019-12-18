#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* rsa; } ;
struct TYPE_9__ {TYPE_2__ pkey; } ;
struct TYPE_8__ {TYPE_5__* pkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  const* n; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_3__ K ;
typedef  int /*<<< orphan*/  BUF ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BigNumToBuf (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_RSA (TYPE_5__*) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

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