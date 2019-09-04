#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct cpx {int /*<<< orphan*/  cpx_iv_aes_ctx; int /*<<< orphan*/  cpx_flags; int /*<<< orphan*/  cpx_key_len; int /*<<< orphan*/  cpx_cached_key; } ;
typedef  int /*<<< orphan*/  aes_encrypt_ctx ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CPX_IV_AES_CTX_INITIALIZED ; 
 int /*<<< orphan*/  CPX_IV_AES_CTX_VFS ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  cpx_set_aes_iv_key (struct cpx*,int /*<<< orphan*/ *) ; 

aes_encrypt_ctx *cpx_iv_aes_ctx(struct cpx *cpx)
{
	if (ISSET(cpx->cpx_flags, CPX_IV_AES_CTX_INITIALIZED))
	return &cpx->cpx_iv_aes_ctx;

	SHA1_CTX sha1ctxt;
	uint8_t digest[SHA_DIGEST_LENGTH]; /* Kiv */

	/* First init the cp_cache_iv_key[] */
	SHA1Init(&sha1ctxt);

	/*
	 * We can only use this when the keys are generated in the AP; As a result
	 * we only use the first 32 bytes of key length in the cache key
	 */
	SHA1Update(&sha1ctxt, cpx->cpx_cached_key, cpx->cpx_key_len);
	SHA1Final(digest, &sha1ctxt);

	cpx_set_aes_iv_key(cpx, digest);
	SET(cpx->cpx_flags, CPX_IV_AES_CTX_VFS);

	return &cpx->cpx_iv_aes_ctx;
}