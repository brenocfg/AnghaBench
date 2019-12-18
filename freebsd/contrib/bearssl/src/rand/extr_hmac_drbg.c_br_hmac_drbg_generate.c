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
struct TYPE_3__ {unsigned char* K; unsigned char* V; int /*<<< orphan*/ * digest_class; } ;
typedef  TYPE_1__ br_hmac_drbg_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 size_t br_digest_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

void
br_hmac_drbg_generate(br_hmac_drbg_context *ctx, void *out, size_t len)
{
	const br_hash_class *dig;
	br_hmac_key_context kc;
	br_hmac_context hc;
	size_t hlen;
	unsigned char *buf;
	unsigned char x;

	dig = ctx->digest_class;
	hlen = br_digest_size(dig);
	br_hmac_key_init(&kc, dig, ctx->K, hlen);
	buf = out;
	while (len > 0) {
		size_t clen;

		br_hmac_init(&hc, &kc, 0);
		br_hmac_update(&hc, ctx->V, hlen);
		br_hmac_out(&hc, ctx->V);
		clen = hlen;
		if (clen > len) {
			clen = len;
		}
		memcpy(buf, ctx->V, clen);
		buf += clen;
		len -= clen;
	}

	/*
	 * To prepare the state for the next request, we should call
	 * br_hmac_drbg_update() with an empty additional seed. However,
	 * we already have an initialized HMAC context with the right
	 * initial key, and we don't want to push another one on the
	 * stack, so we inline that update() call here.
	 */
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	x = 0x00;
	br_hmac_update(&hc, &x, 1);
	br_hmac_out(&hc, ctx->K);
	br_hmac_key_init(&kc, dig, ctx->K, hlen);
	br_hmac_init(&hc, &kc, 0);
	br_hmac_update(&hc, ctx->V, hlen);
	br_hmac_out(&hc, ctx->V);
}