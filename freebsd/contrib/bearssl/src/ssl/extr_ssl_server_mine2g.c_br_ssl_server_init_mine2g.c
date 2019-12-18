#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  br_x509_certificate ;
struct TYPE_5__ {int /*<<< orphan*/  eng; } ;
typedef  TYPE_1__ br_ssl_server_context ;
typedef  int /*<<< orphan*/  br_rsa_private_key ;

/* Variables and functions */
 int /*<<< orphan*/  BR_KEYTYPE_SIGN ; 
 int /*<<< orphan*/  BR_TLS12 ; 
#define  BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 128 
 int /*<<< orphan*/  br_ec_all_m15 ; 
 int /*<<< orphan*/  br_rsa_i31_pkcs1_sign ; 
 int /*<<< orphan*/  br_sha256_ID ; 
 int /*<<< orphan*/  br_sha256_vtable ; 
 int /*<<< orphan*/  br_ssl_engine_set_default_aes_gcm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_ec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_prf_sha256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_suites (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  br_ssl_engine_set_versions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_server_set_single_rsa (TYPE_1__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_server_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  br_tls12_sha256_prf ; 

void
br_ssl_server_init_mine2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk)
{
	static const uint16_t suites[] = {
		BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
	};

	/*
	 * Reset server context and set supported versions to TLS-1.2 (only).
	 */
	br_ssl_server_zero(cc);
	br_ssl_engine_set_versions(&cc->eng, BR_TLS12, BR_TLS12);

	/*
	 * Set suites and elliptic curve implementation (for ECDHE).
	 */
	br_ssl_engine_set_suites(&cc->eng, suites,
		(sizeof suites) / (sizeof suites[0]));
	br_ssl_engine_set_ec(&cc->eng, &br_ec_all_m15);

	/*
	 * Set the "server policy": handler for the certificate chain
	 * and private key operations.
	 */
	br_ssl_server_set_single_rsa(cc, chain, chain_len, sk,
		BR_KEYTYPE_SIGN, 0, br_rsa_i31_pkcs1_sign);

	/*
	 * Set supported hash functions.
	 */
	br_ssl_engine_set_hash(&cc->eng, br_sha256_ID, &br_sha256_vtable);

	/*
	 * Set the PRF implementations.
	 */
	br_ssl_engine_set_prf_sha256(&cc->eng, &br_tls12_sha256_prf);

	/*
	 * Symmetric encryption.
	 */
	br_ssl_engine_set_default_aes_gcm(&cc->eng);
}