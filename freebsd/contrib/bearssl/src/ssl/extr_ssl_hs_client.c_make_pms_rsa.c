#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned char* n; size_t nlen; } ;
struct TYPE_10__ {TYPE_5__ rsa; } ;
struct TYPE_11__ {TYPE_1__ key; } ;
typedef  TYPE_2__ br_x509_pkey ;
struct TYPE_12__ {TYPE_2__* (* get_pkey ) (TYPE_3__ const**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ br_x509_class ;
struct TYPE_15__ {unsigned char* pad; int /*<<< orphan*/  rng; int /*<<< orphan*/  version_max; TYPE_3__** x509ctx; } ;
struct TYPE_13__ {TYPE_9__ eng; int /*<<< orphan*/  (* irsapub ) (unsigned char*,size_t,TYPE_5__*) ;} ;
typedef  TYPE_4__ br_ssl_client_context ;

/* Variables and functions */
 int BR_ERR_LIMIT_EXCEEDED ; 
 int BR_ERR_X509_WEAK_PUBLIC_KEY ; 
 int /*<<< orphan*/  br_enc16be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_drbg_generate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_ssl_engine_compute_master (TYPE_9__*,int,unsigned char*,int) ; 
 TYPE_2__* stub1 (TYPE_3__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,size_t,TYPE_5__*) ; 

__attribute__((used)) static int
make_pms_rsa(br_ssl_client_context *ctx, int prf_id)
{
	const br_x509_class **xc;
	const br_x509_pkey *pk;
	const unsigned char *n;
	unsigned char *pms;
	size_t nlen, u;

	xc = ctx->eng.x509ctx;
	pk = (*xc)->get_pkey(xc, NULL);

	/*
	 * Compute actual RSA key length, in case there are leading zeros.
	 */
	n = pk->key.rsa.n;
	nlen = pk->key.rsa.nlen;
	while (nlen > 0 && *n == 0) {
		n ++;
		nlen --;
	}

	/*
	 * We need at least 59 bytes (48 bytes for pre-master secret, and
	 * 11 bytes for the PKCS#1 type 2 padding). Note that the X.509
	 * minimal engine normally blocks RSA keys shorter than 128 bytes,
	 * so this is mostly for public keys provided explicitly by the
	 * caller.
	 */
	if (nlen < 59) {
		return -BR_ERR_X509_WEAK_PUBLIC_KEY;
	}
	if (nlen > sizeof ctx->eng.pad) {
		return -BR_ERR_LIMIT_EXCEEDED;
	}

	/*
	 * Make PMS.
	 */
	pms = ctx->eng.pad + nlen - 48;
	br_enc16be(pms, ctx->eng.version_max);
	br_hmac_drbg_generate(&ctx->eng.rng, pms + 2, 46);
	br_ssl_engine_compute_master(&ctx->eng, prf_id, pms, 48);

	/*
	 * Apply PKCS#1 type 2 padding.
	 */
	ctx->eng.pad[0] = 0x00;
	ctx->eng.pad[1] = 0x02;
	ctx->eng.pad[nlen - 49] = 0x00;
	br_hmac_drbg_generate(&ctx->eng.rng, ctx->eng.pad + 2, nlen - 51);
	for (u = 2; u < nlen - 49; u ++) {
		while (ctx->eng.pad[u] == 0) {
			br_hmac_drbg_generate(&ctx->eng.rng,
				&ctx->eng.pad[u], 1);
		}
	}

	/*
	 * Compute RSA encryption.
	 */
	if (!ctx->irsapub(ctx->eng.pad, nlen, &pk->key.rsa)) {
		return -BR_ERR_LIMIT_EXCEEDED;
	}
	return (int)nlen;
}