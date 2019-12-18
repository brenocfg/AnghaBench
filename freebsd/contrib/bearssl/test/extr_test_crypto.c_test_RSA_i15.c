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

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i15_compute_modulus ; 
 int /*<<< orphan*/  br_rsa_i15_compute_privexp ; 
 int /*<<< orphan*/  br_rsa_i15_compute_pubexp ; 
 int /*<<< orphan*/  br_rsa_i15_keygen ; 
 int /*<<< orphan*/  br_rsa_i15_oaep_decrypt ; 
 int /*<<< orphan*/  br_rsa_i15_oaep_encrypt ; 
 int /*<<< orphan*/  br_rsa_i15_pkcs1_sign ; 
 int /*<<< orphan*/  br_rsa_i15_pkcs1_vrfy ; 
 int /*<<< orphan*/  br_rsa_i15_private ; 
 int /*<<< orphan*/  br_rsa_i15_pss_sign ; 
 int /*<<< orphan*/  br_rsa_i15_pss_vrfy ; 
 int /*<<< orphan*/  br_rsa_i15_public ; 
 int /*<<< orphan*/  test_RSA_OAEP (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_PSS (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_core (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_keygen (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_RSA_sign (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_RSA_i15(void)
{
	test_RSA_core("RSA i15 core", &br_rsa_i15_public, &br_rsa_i15_private);
	test_RSA_sign("RSA i15 sign", &br_rsa_i15_private,
		&br_rsa_i15_pkcs1_sign, &br_rsa_i15_pkcs1_vrfy);
	test_RSA_OAEP("RSA i15 OAEP",
		&br_rsa_i15_oaep_encrypt, &br_rsa_i15_oaep_decrypt);
	test_RSA_PSS("RSA i15 PSS",
		&br_rsa_i15_pss_sign, &br_rsa_i15_pss_vrfy);
	test_RSA_keygen("RSA i15 keygen", &br_rsa_i15_keygen,
		&br_rsa_i15_compute_modulus, &br_rsa_i15_compute_pubexp,
		&br_rsa_i15_compute_privexp, &br_rsa_i15_public,
		&br_rsa_i15_pkcs1_sign, &br_rsa_i15_pkcs1_vrfy);
}