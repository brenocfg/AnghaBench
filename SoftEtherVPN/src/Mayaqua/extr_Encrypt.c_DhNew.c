#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  const* priv_key; int /*<<< orphan*/  const* pub_key; int /*<<< orphan*/ * g; void* p; } ;
struct TYPE_12__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  Size; TYPE_7__* dh; void* MyPrivateKey; void* MyPublicKey; } ;
typedef  TYPE_1__ DH_CTX ;
typedef  TYPE_2__ BUF ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 void* BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* BigNumToBuf (int /*<<< orphan*/  const*) ; 
 void* BinToBigNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DH_generate_key (TYPE_7__*) ; 
 int /*<<< orphan*/  DH_get0_key (TYPE_7__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 TYPE_7__* DH_new () ; 
 int /*<<< orphan*/  DH_set0_pqg (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* StrToBin (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

DH_CTX *DhNew(char *prime, UINT g)
{
	DH_CTX *dh;
	BUF *buf;
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	BIGNUM *dhp, *dhg;
	const BIGNUM *pub, *priv;
#endif
	// Validate arguments
	if (prime == NULL || g == 0)
	{
		return NULL;
	}

	buf = StrToBin(prime);

	dh = ZeroMalloc(sizeof(DH_CTX));

	dh->dh = DH_new();
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	dhp = BinToBigNum(buf->Buf, buf->Size);
	dhg = BN_new();
	BN_set_word(dhg, g);
	DH_set0_pqg(dh->dh, dhp, NULL, dhg);
#else
	dh->dh->p = BinToBigNum(buf->Buf, buf->Size);
	dh->dh->g = BN_new();
	BN_set_word(dh->dh->g, g);
#endif

	DH_generate_key(dh->dh);

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	DH_get0_key(dh->dh, &pub, &priv);
	dh->MyPublicKey = BigNumToBuf(pub);
	dh->MyPrivateKey = BigNumToBuf(priv);
#else
	dh->MyPublicKey = BigNumToBuf(dh->dh->pub_key);
	dh->MyPrivateKey = BigNumToBuf(dh->dh->priv_key);
#endif

	dh->Size = buf->Size;

	FreeBuf(buf);

	return dh;
}