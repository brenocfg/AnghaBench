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
 int BR_KEYTYPE_KEYX ; 
 int BR_KEYTYPE_SIGN ; 
 int /*<<< orphan*/  BR_TLS10 ; 
 int /*<<< orphan*/  BR_TLS12 ; 
#define  BR_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA 141 
#define  BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA 140 
#define  BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 139 
#define  BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 138 
#define  BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA 137 
#define  BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 136 
#define  BR_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 135 
#define  BR_TLS_RSA_WITH_3DES_EDE_CBC_SHA 134 
#define  BR_TLS_RSA_WITH_AES_128_CBC_SHA 133 
#define  BR_TLS_RSA_WITH_AES_128_CBC_SHA256 132 
#define  BR_TLS_RSA_WITH_AES_128_GCM_SHA256 131 
#define  BR_TLS_RSA_WITH_AES_256_CBC_SHA 130 
#define  BR_TLS_RSA_WITH_AES_256_CBC_SHA256 129 
#define  BR_TLS_RSA_WITH_AES_256_GCM_SHA384 128 
 int /*<<< orphan*/  br_aes_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  br_aes_ct_cbcenc_vtable ; 
 int /*<<< orphan*/  br_aes_ct_ctr_vtable ; 
 int /*<<< orphan*/  br_des_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  br_des_ct_cbcenc_vtable ; 
 int /*<<< orphan*/  br_ec_prime_i31 ; 
 int /*<<< orphan*/  br_ghash_ctmul ; 
 int /*<<< orphan*/  br_md5_ID ; 
 int /*<<< orphan*/  br_md5_vtable ; 
 int /*<<< orphan*/  br_rsa_i31_pkcs1_sign ; 
 int /*<<< orphan*/  br_rsa_i31_private ; 
 int /*<<< orphan*/  br_sha1_ID ; 
 int /*<<< orphan*/  br_sha1_vtable ; 
 int /*<<< orphan*/  br_sha224_ID ; 
 int /*<<< orphan*/  br_sha224_vtable ; 
 int /*<<< orphan*/  br_sha256_ID ; 
 int /*<<< orphan*/  br_sha256_vtable ; 
 int /*<<< orphan*/  br_sha384_ID ; 
 int /*<<< orphan*/  br_sha384_vtable ; 
 int /*<<< orphan*/  br_sha512_ID ; 
 int /*<<< orphan*/  br_sha512_vtable ; 
 int /*<<< orphan*/  br_ssl_engine_set_aes_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_aes_ctr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_des_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_ec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_gcm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_ghash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_prf10 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_prf_sha256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_prf_sha384 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_suites (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  br_ssl_engine_set_versions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_server_set_single_rsa (TYPE_1__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_server_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  br_sslrec_in_cbc_vtable ; 
 int /*<<< orphan*/  br_sslrec_in_gcm_vtable ; 
 int /*<<< orphan*/  br_sslrec_out_cbc_vtable ; 
 int /*<<< orphan*/  br_sslrec_out_gcm_vtable ; 
 int /*<<< orphan*/  br_tls10_prf ; 
 int /*<<< orphan*/  br_tls12_sha256_prf ; 
 int /*<<< orphan*/  br_tls12_sha384_prf ; 

void
example_server_profile(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk)
{
	static const uint16_t suites[] = {
		BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
		BR_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
		BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,
		BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,
		BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,
		BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
		BR_TLS_RSA_WITH_AES_128_GCM_SHA256,
		BR_TLS_RSA_WITH_AES_256_GCM_SHA384,
		BR_TLS_RSA_WITH_AES_128_CBC_SHA256,
		BR_TLS_RSA_WITH_AES_256_CBC_SHA256,
		BR_TLS_RSA_WITH_AES_128_CBC_SHA,
		BR_TLS_RSA_WITH_AES_256_CBC_SHA,
		BR_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,
		BR_TLS_RSA_WITH_3DES_EDE_CBC_SHA
	};

	br_ssl_server_zero(cc);
	br_ssl_engine_set_versions(&cc->eng, BR_TLS10, BR_TLS12);

	br_ssl_engine_set_prf10(&cc->eng, &br_tls10_prf);
	br_ssl_engine_set_prf_sha256(&cc->eng, &br_tls12_sha256_prf);
	br_ssl_engine_set_prf_sha384(&cc->eng, &br_tls12_sha384_prf);

	/*
	 * Apart from the requirements listed in the client side, these
	 * hash functions are also used by the server to compute its
	 * signature on ECDHE parameters. Which functions are needed
	 * depends on what the client may support; furthermore, the
	 * client may fail to send the relevant extension, in which
	 * case the server will default to whatever it can (as per the
	 * standard, it should be SHA-1 in that case).
	 */
	br_ssl_engine_set_hash(&cc->eng, br_md5_ID, &br_md5_vtable);
	br_ssl_engine_set_hash(&cc->eng, br_sha1_ID, &br_sha1_vtable);
	br_ssl_engine_set_hash(&cc->eng, br_sha224_ID, &br_sha224_vtable);
	br_ssl_engine_set_hash(&cc->eng, br_sha256_ID, &br_sha256_vtable);
	br_ssl_engine_set_hash(&cc->eng, br_sha384_ID, &br_sha384_vtable);
	br_ssl_engine_set_hash(&cc->eng, br_sha512_ID, &br_sha512_vtable);

	br_ssl_engine_set_suites(&cc->eng, suites,
		(sizeof suites) / (sizeof suites[0]));

	/*
	 * Elliptic curve implementation is used for ECDHE suites (but
	 * not for ECDH).
	 */
	br_ssl_engine_set_ec(&cc->eng, &br_ec_prime_i31);

	/*
	 * Set the "server policy": handler for the certificate chain
	 * and private key operations. Here, we indicate that the RSA
	 * private key is fit for both signing and decrypting, and we
	 * provide the two relevant implementations.

	 * BR_KEYTYPE_KEYX allows TLS_RSA_*, BR_KEYTYPE_SIGN allows
	 * TLS_ECDHE_RSA_*.
	 */
	br_ssl_server_set_single_rsa(cc, chain, chain_len, sk,
		BR_KEYTYPE_KEYX | BR_KEYTYPE_SIGN,
		br_rsa_i31_private, br_rsa_i31_pkcs1_sign);
	/*
	 * If the server used an EC private key, this call would look
	 * like this:

	br_ssl_server_set_single_ec(cc, chain, chain_len, sk,
		BR_KEYTYPE_KEYX | BR_KEYTYPE_SIGN,
		cert_issuer_key_type,
		&br_ec_prime_i31, br_ecdsa_i31_sign_asn1);

	 * Note the tricky points:
	 *
	 * -- "ECDH" cipher suites use only the EC code (&br_ec_prime_i31);
	 *    the ECDHE_ECDSA cipher suites need both the EC code and
	 *    the ECDSA signature implementation.
	 *
	 * -- For "ECDH" (not "ECDHE") cipher suites, the engine must
	 *    know the key type (RSA or EC) for the intermediate CA that
	 *    issued the server's certificate; this is an artefact of
	 *    how the protocol is defined. BearSSL won't try to decode
	 *    the server's certificate to obtain that information (it
	 *    could do that, the code is there, but it would increase the
	 *    footprint). So this must be provided by the caller.
	 *
	 * -- BR_KEYTYPE_KEYX allows ECDH, BR_KEYTYPE_SIGN allows
	 *    ECDHE_ECDSA.
	 */

	br_ssl_engine_set_cbc(&cc->eng,
		&br_sslrec_in_cbc_vtable,
		&br_sslrec_out_cbc_vtable);
	br_ssl_engine_set_gcm(&cc->eng,
		&br_sslrec_in_gcm_vtable,
		&br_sslrec_out_gcm_vtable);

	br_ssl_engine_set_aes_cbc(&cc->eng,
		&br_aes_ct_cbcenc_vtable,
		&br_aes_ct_cbcdec_vtable);
	br_ssl_engine_set_aes_ctr(&cc->eng,
		&br_aes_ct_ctr_vtable);
	/* Alternate: aes_ct64
	br_ssl_engine_set_aes_cbc(&cc->eng,
		&br_aes_ct64_cbcenc_vtable,
		&br_aes_ct64_cbcdec_vtable);
	br_ssl_engine_set_aes_ctr(&cc->eng,
		&br_aes_ct64_ctr_vtable);
	*/
	/* Alternate: aes_small
	br_ssl_engine_set_aes_cbc(&cc->eng,
		&br_aes_small_cbcenc_vtable,
		&br_aes_small_cbcdec_vtable);
	br_ssl_engine_set_aes_ctr(&cc->eng,
		&br_aes_small_ctr_vtable);
	*/
	/* Alternate: aes_big
	br_ssl_engine_set_aes_cbc(&cc->eng,
		&br_aes_big_cbcenc_vtable,
		&br_aes_big_cbcdec_vtable);
	br_ssl_engine_set_aes_ctr(&cc->eng,
		&br_aes_big_ctr_vtable);
	*/
	br_ssl_engine_set_des_cbc(&cc->eng,
		&br_des_ct_cbcenc_vtable,
		&br_des_ct_cbcdec_vtable);
	/* Alternate: des_tab
	br_ssl_engine_set_des_cbc(&cc->eng,
		&br_des_tab_cbcenc_vtable,
		&br_des_tab_cbcdec_vtable);
	*/

	br_ssl_engine_set_ghash(&cc->eng,
		&br_ghash_ctmul);
	/* Alternate: ghash_ctmul32
	br_ssl_engine_set_ghash(&cc->eng,
		&br_ghash_ctmul32);
	*/
	/* Alternate: ghash_ctmul64
	br_ssl_engine_set_ghash(&cc->eng,
		&br_ghash_ctmul64);
	*/
}