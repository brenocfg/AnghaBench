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
struct TYPE_4__ {int rng_init_done; int /*<<< orphan*/  rng; int /*<<< orphan*/  mhash; } ;
typedef  TYPE_1__ br_ssl_engine_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/  BR_ERR_BAD_STATE ; 
 int /*<<< orphan*/  br_hmac_drbg_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * br_multihash_getimpl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_sha1_ID ; 
 int /*<<< orphan*/  br_sha256_ID ; 
 int /*<<< orphan*/  br_sha384_ID ; 
 int /*<<< orphan*/  br_ssl_engine_fail (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rng_init(br_ssl_engine_context *cc)
{
	const br_hash_class *h;

	if (cc->rng_init_done != 0) {
		return 1;
	}

	/*
	 * If using TLS-1.2, then SHA-256 or SHA-384 must be present (or
	 * both); we prefer SHA-256 which is faster for 32-bit systems.
	 *
	 * If using TLS-1.0 or 1.1 then SHA-1 must be present.
	 *
	 * Though HMAC_DRBG/SHA-1 is, as far as we know, as safe as
	 * these things can be, we still prefer the SHA-2 functions over
	 * SHA-1, if only for public relations (known theoretical
	 * weaknesses of SHA-1 with regards to collisions are mostly
	 * irrelevant here, but they still make people nervous).
	 */
	h = br_multihash_getimpl(&cc->mhash, br_sha256_ID);
	if (!h) {
		h = br_multihash_getimpl(&cc->mhash, br_sha384_ID);
		if (!h) {
			h = br_multihash_getimpl(&cc->mhash,
				br_sha1_ID);
			if (!h) {
				br_ssl_engine_fail(cc, BR_ERR_BAD_STATE);
				return 0;
			}
		}
	}
	br_hmac_drbg_init(&cc->rng, h, NULL, 0);
	cc->rng_init_done = 1;
	return 1;
}