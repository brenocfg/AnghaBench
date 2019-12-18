#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  br_hmac_key_context ;
struct TYPE_3__ {void const* K; void const* V; int /*<<< orphan*/ * digest_class; } ;
typedef  TYPE_1__ br_hmac_drbg_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 size_t br_digest_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,void const*,size_t) ; 

void
br_hmac_drbg_update(br_hmac_drbg_context *ctx, const void *seed, size_t len)
{
	const br_hash_class *dig;
	br_hmac_key_context kc;
	br_hmac_context hc;
	size_t hlen;
	unsigned char x;

	dig = ctx->digest_class;
	hlen = br_digest_size(dig);

	/*
	 * 1. K = HMAC(K, V || 0x00 || seed)
	 */
	br_hmac_key_init(&kc, dig, ctx->K, hlen);
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	x = 0x00;
	br_hmac_update(&hc, &x, 1);
	br_hmac_update(&hc, seed, len);
	br_hmac_out(&hc, ctx->K);
	br_hmac_key_init(&kc, dig, ctx->K, hlen);

	/*
	 * 2. V = HMAC(K, V)
	 */
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	br_hmac_out(&hc, ctx->V);

	/*
	 * 3. If the additional seed is empty, then stop here.
	 */
	if (len == 0) {
		return;
	}

	/*
	 * 4. K = HMAC(K, V || 0x01 || seed)
	 */
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	x = 0x01;
	br_hmac_update(&hc, &x, 1);
	br_hmac_update(&hc, seed, len);
	br_hmac_out(&hc, ctx->K);
	br_hmac_key_init(&kc, dig, ctx->K, hlen);

	/*
	 * 5. V = HMAC(K, V)
	 */
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	br_hmac_out(&hc, ctx->V);
}