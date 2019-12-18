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
typedef  scalar_t__ br_rsa_public ;
typedef  scalar_t__ br_rsa_pss_vrfy ;
typedef  scalar_t__ br_rsa_pss_sign ;
typedef  scalar_t__ br_rsa_private ;
typedef  scalar_t__ br_rsa_pkcs1_vrfy ;
typedef  scalar_t__ br_rsa_pkcs1_sign ;
typedef  scalar_t__ br_rsa_oaep_encrypt ;
typedef  scalar_t__ br_rsa_oaep_decrypt ;
typedef  scalar_t__ br_rsa_keygen ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  br_rsa_i31_compute_modulus ; 
 int /*<<< orphan*/  br_rsa_i31_compute_privexp ; 
 int /*<<< orphan*/  br_rsa_i31_compute_pubexp ; 
 scalar_t__ br_rsa_i62_keygen_get () ; 
 scalar_t__ br_rsa_i62_oaep_decrypt_get () ; 
 scalar_t__ br_rsa_i62_oaep_encrypt_get () ; 
 scalar_t__ br_rsa_i62_pkcs1_sign_get () ; 
 scalar_t__ br_rsa_i62_pkcs1_vrfy_get () ; 
 scalar_t__ br_rsa_i62_private_get () ; 
 scalar_t__ br_rsa_i62_pss_sign_get () ; 
 scalar_t__ br_rsa_i62_pss_vrfy_get () ; 
 scalar_t__ br_rsa_i62_public_get () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_RSA_OAEP (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_RSA_PSS (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_RSA_core (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_RSA_keygen (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_RSA_sign (char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
test_RSA_i62(void)
{
	br_rsa_public pub;
	br_rsa_private priv;
	br_rsa_pkcs1_sign sign;
	br_rsa_pkcs1_vrfy vrfy;
	br_rsa_pss_sign pss_sign;
	br_rsa_pss_vrfy pss_vrfy;
	br_rsa_oaep_encrypt menc;
	br_rsa_oaep_decrypt mdec;
	br_rsa_keygen kgen;

	pub = br_rsa_i62_public_get();
	priv = br_rsa_i62_private_get();
	sign = br_rsa_i62_pkcs1_sign_get();
	vrfy = br_rsa_i62_pkcs1_vrfy_get();
	pss_sign = br_rsa_i62_pss_sign_get();
	pss_vrfy = br_rsa_i62_pss_vrfy_get();
	menc = br_rsa_i62_oaep_encrypt_get();
	mdec = br_rsa_i62_oaep_decrypt_get();
	kgen = br_rsa_i62_keygen_get();
	if (pub) {
		if (!priv || !sign || !vrfy || !pss_sign || !pss_vrfy
			|| !menc || !mdec || !kgen)
		{
			fprintf(stderr, "Inconsistent i62 availability\n");
			exit(EXIT_FAILURE);
		}
		test_RSA_core("RSA i62 core", pub, priv);
		test_RSA_sign("RSA i62 sign", priv, sign, vrfy);
		test_RSA_OAEP("RSA i62 OAEP", menc, mdec);
		test_RSA_PSS("RSA i62 PSS", pss_sign, pss_vrfy);
		test_RSA_keygen("RSA i62 keygen", kgen,
			&br_rsa_i31_compute_modulus, &br_rsa_i31_compute_pubexp,
			&br_rsa_i31_compute_privexp, pub,
			sign, vrfy);
	} else {
		if (priv || sign || vrfy || pss_sign || pss_vrfy
			|| menc || mdec || kgen)
		{
			fprintf(stderr, "Inconsistent i62 availability\n");
			exit(EXIT_FAILURE);
		}
		printf("Test RSA i62: UNAVAILABLE\n");
	}
}